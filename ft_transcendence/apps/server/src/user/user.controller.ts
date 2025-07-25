import {
  Controller,
  Get,
  Post,
  Req,
  Res,
  UploadedFile,
  UseInterceptors,
} from '@nestjs/common';
import { FileInterceptor } from '@nestjs/platform-express';
import { AuthService } from '@server/auth/auth.service';
import { PrismaService } from '@server/prisma/prisma.service';
import { Request, Response } from 'express';
import { z } from 'zod';
import { sendEmail } from '@server/utils/mail/util/send';
import * as crypto from 'crypto';
import * as bcrypt from 'bcrypt';
import { FriendService } from '@server/friend/friend.service';
import { UserService } from './user.service';
import { format } from 'date-fns';

@Controller('user')
export class UserController {
  constructor(
    private prisma: PrismaService,
    private authService: AuthService,
    private friendService: FriendService,
    private userService: UserService,
  ) {}

  @Get('/me')
  async me(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    return res.status(200).json({
      ...user,
      notifications: {
        chats: 0, // TODO: IMPLEMENT CHATS
        friendRequests: (await this.friendService.getAllFriendsTypes(user.id))
          .pending.length,
      },
    });
  }

  @Post('/username')
  async username(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const schema = z.object({
      username: z
        .string()
        .min(1)
        .max(20)
        .regex(/^[a-zA-Z0-9_]+$/),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid username provided' });
    }
    const { username } = schema.parse(req.body);

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const existingUser = await this.prisma.user.findUnique({
      where: { username: username },
    });

    if (existingUser) {
      return res.status(400).send({ error: 'Username already taken' });
    }

    const updatedUser = await this.prisma.user.update({
      where: { id: user.id },
      data: { username: username },
    });

    return res.status(200).send(updatedUser);
  }

  @Post('2fa')
  async tfa(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const schema = z.object({
      email: z.string().regex(/^.+@.+\..+$/),
      tfaEnabled: z.boolean(),
    });
    if (!schema.safeParse(req.body).success) {
      return res
        .status(400)
        .send({ error: 'Invalid body, missing either email or tfaEnabled' });
    }
    const { tfaEnabled, email } = schema.parse(req.body);

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    // if tfa is disabled and user doesn't want to enable it
    if (!user.tfaEnabled && !user.tfaVerified && !tfaEnabled) {
      const newUser = await this.prisma.user.update({
        where: { id: user.id },
        data: { email: email, tfaEnabled: false, tfaVerified: false },
      });
      return res.status(200).send(newUser);
    }

    // VERIFY 2FA STUFF
    const OTPToken = crypto
      .randomInt(99999999)
      .toString()
      .padStart('99999999'.length, '0');
    // store OTP in db
    const hash = await bcrypt.hash(OTPToken, 10);
    await this.prisma.user.update({
      where: { id: user.id },
      data: {
        tfaOTP: hash,
        tfaOTPCreatedAt: new Date(),
      },
    });
    // send otp to email
    try {
      const status = await sendEmail({
        to: user.tfaEnabled ? user.email : email,
        templateId: 'newUser',
        context: {
          token: OTPToken,
        },
      });
      if (!status) {
        return res.status(500).json({
          success: false,
          error: 'Failed to send email',
        });
      }
    } catch (error) {
      return res.status(500).json({
        success: false,
        error: 'Failed to send email',
      });
    }
    // send OTP step to client
    return res.status(200).json({
      success: true,
      otp: true,
      email: user.email,
    });
  }

  @Post('pfp')
  @UseInterceptors(FileInterceptor('file'))
  async pfp(
    @Req() req: Request,
    @Res() res: Response,
    @UploadedFile() file: Express.Multer.File,
  ) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    if (
      !file ||
      !file.buffer ||
      (file.mimetype !== 'image/png' && file.mimetype !== 'image/jpeg')
    ) {
      return res.status(400).json({ error: 'No/Invalid file provided' });
    }

    if (file.size > 1024 * 1024 * 5) {
      return res.status(400).json({ error: 'File too large, over 5MB' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const updatedUser = await this.prisma.user.update({
      where: { id: user.id },
      data: { pfp: 'data:image/png;base64,' + file.buffer.toString('base64') },
    });

    res.status(200).send(updatedUser);
  }

  @Get('all')
  async getAllUser(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const reqUser = await this.authService.getLoggedInUser(req);
    if (!reqUser) {
      return res.status(400).send({ error: 'No user found' });
    }

    const users = await this.prisma.user.findMany({
      where: {},
      select: {
        id: true,
        username: true,
        pfp: true,
        status: true,
        inGame: true,
        createdAt: true,
        updatedAt: true,
      },
    });

    const friends = await this.friendService.getAllFriendsTypes(reqUser.id);
    const newUsers = [];
    for (const user of users) {
      if (!user) continue;
      if (user.id === reqUser.id) continue;
      let isFriend = false;
      for (const friend of friends.friends) {
        if (!friend) continue;
        if (friend.id === user.id) {
          isFriend = true;
          break;
        }
      }
      newUsers.push({ ...user, isFriend: isFriend });
    }

    return res.status(200).send(newUsers);
  }

  @Get(':id')
  async getUser(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const reqUser = await this.authService.getLoggedInUser(req);
    if (!reqUser) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      id: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.params).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.params);

    const user = await this.prisma.user.findUnique({
      where: { id: id },
      select: {
        id: true,
        username: true,
        pfp: true,
        status: true,
        inGame: true,
        createdAt: true,
        updatedAt: true,
        blocked: true,
        blockedBy: true,
      },
    });

    if (!user) {
      return res.status(404).send({ error: 'No user found' });
    }

    const friends = await this.friendService.getAllFriendsTypes(reqUser.id);
    let isFriend = false;
    for (const friend of friends.friends) {
      if (!friend) continue;
      if (friend.id === id) {
        isFriend = true;
        break;
      }
    }

    const gamesWon = await this.prisma.game.findMany({
      where: {
        OR: [{ winnerId: id }],
      },
    });

    const gamesLost = await this.prisma.game.findMany({
      where: {
        OR: [{ loserId: id }],
      },
    });

    const data: any = user;
    data.isOwnProfile = reqUser.id === user.id;
    data.isFriend = isFriend;
    data.isBlocked = data.isOwnProfile
      ? false
      : user.blockedBy.some((b) => b.user_id === reqUser.id);
    data.ranking = await this.userService.getRanking(reqUser.id);
    data.totalGamesPlayed = gamesWon.length + gamesLost.length;
    if (gamesLost.length == 0) {
      data.ratioWL = Math.round((gamesWon.length / 1) * 100) / 100;
    } else {
      data.ratioWL =
        Math.round((gamesWon.length / gamesLost.length) * 100) / 100;
    }

    if (!user) {
      return res.status(404).send({ error: 'No user found' });
    }

    return res.status(200).send(user);
  }

  @Get(':id/game')
  async getGames(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const reqUser = await this.authService.getLoggedInUser(req);
    if (!reqUser) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      id: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.params).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.params);

    const user = await this.prisma.user.findUnique({
      where: { id: id },
      select: {
        id: true,
        username: true,
        pfp: true,
        status: true,
        inGame: true,
        createdAt: true,
        updatedAt: true,
        blocked: true,
        blockedBy: true,
      },
    });

    if (!user) {
      return res.status(404).send({ error: 'No user found' });
    }

    const games = await this.prisma.game.findMany({
      where: {
        OR: [{ winnerId: id }, { loserId: id }],
      },
      include: {
        loser: {
          select: {
            username: true,
            id: true,
          },
        },
        winner: {
          select: {
            username: true,
            id: true,
          },
        },
      },
      orderBy: {
        createdAt: 'desc',
      },
    });

    const result = games.map((game) => {
      return {
        id: game.id,
        date: format(game.createdAt, 'yyyy-MM-dd'),
        status: game.winnerId === user.id ? 'won' : 'lost',
        opponent:
          game.winnerId === user.id
            ? game.loser.username
            : game.winner.username,
        mode: game.mode,
      };
    });

    return res.status(200).send(result);
  }

  @Post('block')
  async blockUser(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const reqUser = await this.authService.getLoggedInUser(req);
    if (!reqUser) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      id: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.body);

    const u = await this.prisma.user.findUnique({
      where: { id: id },
      select: {
        id: true,
        username: true,
        pfp: true,
        status: true,
        inGame: true,
        createdAt: true,
        updatedAt: true,
      },
    });

    if (!u) {
      return res.status(404).send({ error: 'No user found' });
    }

    const user = await this.prisma.user.findUnique({
      where: { id: reqUser.id },
      select: {
        id: true,
        username: true,
        pfp: true,
        status: true,
        inGame: true,
        createdAt: true,
        updatedAt: true,
        blocked: true,
      },
    });

    if (!user) {
      return res.status(404).send({ error: 'No user found' });
    }

    if (user.blocked.some((b) => b.blockedUser_id === id)) {
      await this.prisma.user.update({
        where: { id: reqUser.id },
        data: {
          blocked: {
            delete: {
              user_id_blockedUser_id: {
                user_id: user.id,
                blockedUser_id: id,
              },
            },
          },
        },
      });

      return res.status(200).send({ success: true, msg: 'User unblocked' });
    }

    await this.prisma.user.update({
      where: { id: reqUser.id },
      data: {
        blocked: {
          create: {
            blockedUser_id: id,
          },
        },
      },
    });

    return res.status(200).send({ success: true, msg: 'User blocked' });
  }
}
