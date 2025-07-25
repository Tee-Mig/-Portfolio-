import { Controller, Get, Post, Req, Res } from '@nestjs/common';
import { AuthService } from '@server/auth/auth.service';
import { PrismaService } from '@server/prisma/prisma.service';
import { Request, Response } from 'express';
import { z } from 'zod';

@Controller('friend')
export class FriendController {
  constructor(
    private prisma: PrismaService,
    private authService: AuthService,
  ) {}

  @Get('/all')
  async getFriends(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const rawFriends = await this.prisma.friend.findMany({
      where: {
        OR: [{ userId: user.id }, { friendId: user.id }],
      },
      include: {
        friend: {
          select: {
            id: true,
            username: true,
            pfp: true,
            status: true,
            inGame: true,
            createdAt: true,
            updatedAt: true,
          },
        },
        user: {
          select: {
            id: true,
            username: true,
            pfp: true,
            status: true,
            inGame: true,
            createdAt: true,
            updatedAt: true,
          },
        },
      },
    });
    if (!rawFriends) {
      return res
        .status(400)
        .send({ success: false, error: 'No friends found' });
    }

    const acceptedFriends = rawFriends.map((friend) => {
      if (friend.accepted) {
        if (friend.userId === user.id) {
          return friend.friend;
        } else {
          return friend.user;
        }
      }
    });
    const pendingFriendRequests = rawFriends.map((friend) => {
      if (!friend.accepted) {
        if (friend.friendId === user.id) {
          return friend.user;
        }
      }
    });

    const sentFriendRequests = rawFriends.map((friend) => {
      if (!friend.accepted) {
        if (friend.userId === user.id) {
          return friend.friend;
        }
      }
    });

    const blockedUsers = await this.prisma.blocked.findMany({
      where: {
        user_id: user.id,
      },
      include: {
        blockedUser: {
          select: {
            id: true,
            username: true,
            pfp: true,
            status: true,
            inGame: true,
            createdAt: true,
            updatedAt: true,
          },
        },
      },
    });

    const bu = blockedUsers.map((user) => user.blockedUser);
    // console.log(blockedUsers);

    return res.status(200).json({
      friends: acceptedFriends.filter((friend) => friend !== undefined),
      pending: pendingFriendRequests.filter((friend) => friend !== undefined),
      sent: sentFriendRequests.filter((friend) => friend !== undefined),
      blocked: bu.filter((friend) => friend !== undefined),
    });
  }

  @Post('/add')
  async addFriend(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      id: z.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.body);

    if (id === user.id) {
      return res.status(400).send({ error: 'Cannot add yourself' });
    }

    const friend = await this.prisma.user.findUnique({
      where: {
        id,
      },
    });
    if (!friend) {
      return res.status(400).send({ error: 'No user found' });
    }

    const existingFriend = await this.prisma.friend.findFirst({
      where: {
        OR: [
          { userId: user.id, friendId: id },
          { userId: id, friendId: user.id },
        ],
      },
    });
    if (existingFriend?.accepted) {
      return res.status(208).send({ msg: 'Already friends' });
    } else if (
      !existingFriend?.accepted &&
      existingFriend?.userId === user.id
    ) {
      return res.status(400).send({ error: 'Friend request already sent' });
    } else if (
      !existingFriend?.accepted &&
      existingFriend?.friendId === user.id
    ) {
      return res.status(208).json({
        success: true,
        msg: 'A friend request is already pending',
      });
    }
    try {
      const newFriend = await this.prisma.friend.create({
        data: {
          userId: user.id,
          friendId: id,
        },
      });
      if (!newFriend) {
        return res.status(400).send({ error: 'Failed to add friend' });
      }
    } catch (err) {
      return res
        .status(400)
        .send({ error: 'A friend request is already pending' });
    }
    return res.status(200).json({ success: true, msg: 'Friend request sent!' });
  }

  @Post('/accept')
  async acceptFriend(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      id: z.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.body);

    if (id === user.id) {
      return res.status(400).send({ error: 'Cannot accept yourself' });
    }

    const friend = await this.prisma.user.findUnique({
      where: {
        id,
      },
    });
    if (!friend) {
      return res.status(400).send({ error: 'No user found' });
    }

    const existingFriend = await this.prisma.friend.findFirst({
      where: {
        OR: [
          { userId: user.id, friendId: id },
          { userId: id, friendId: user.id },
        ],
      },
    });
    if (!existingFriend) {
      return res.status(400).send({ error: 'No friend request found' });
    }

    if (existingFriend.accepted) {
      return res.status(208).send({ msg: 'Already friends' });
    } else if (existingFriend.userId === user.id) {
      return res.status(400).send({ error: 'Friend request already sent' });
    }

    try {
      const updatedFriend = await this.prisma.friend.deleteMany({
        where: {
          OR: [
            { userId: user.id, friendId: id },
            { userId: id, friendId: user.id },
          ],
        },
      });
      if (!updatedFriend) {
        return res.status(400).send({ error: 'Failed to accept friend' });
      }
      const newFriend = await this.prisma.friend.create({
        data: {
          userId: existingFriend.userId,
          friendId: existingFriend.friendId,
          accepted: true,
        },
      });
      if (!newFriend) {
        return res.status(400).send({ error: 'Failed to add friend' });
      }
    } catch (err) {
      return res
        .status(400)
        .send({ error: 'A friend request is already pending' });
    }
    return res.status(200).json({ success: true, msg: 'Friend accepted!' });
  }

  @Post('/refuse')
  async declineFriend(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      id: z.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.body);

    if (id === user.id) {
      return res.status(400).send({ error: 'Cannot refuse yourself' });
    }

    const friend = await this.prisma.user.findUnique({
      where: {
        id,
      },
    });
    if (!friend) {
      return res.status(400).send({ error: 'No user found' });
    }

    const existingFriend = await this.prisma.friend.findFirst({
      where: {
        OR: [
          { userId: user.id, friendId: id, accepted: false },
          { userId: id, friendId: user.id, accepted: false },
        ],
      },
    });
    if (!existingFriend) {
      return res.status(400).send({ error: 'No friend request found' });
    }
    const updatedFriend = await this.prisma.friend.deleteMany({
      where: {
        OR: [
          { userId: user.id, friendId: id },
          { userId: id, friendId: user.id },
        ],
      },
    });
    if (!updatedFriend) {
      return res.status(400).send({ error: 'Failed to refuse friend' });
    }
    return res
      .status(200)
      .json({ success: true, msg: 'Friend request refused!' });
  }

  @Post('/remove')
  async removeFriend(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      id: z.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.body);

    if (id === user.id) {
      return res.status(400).send({ error: 'Cannot remove yourself' });
    }

    const friend = await this.prisma.user.findUnique({
      where: {
        id,
      },
    });
    if (!friend) {
      return res.status(400).send({ error: 'No user found' });
    }

    const existingFriend = await this.prisma.friend.findFirst({
      where: {
        OR: [
          { userId: user.id, friendId: id, accepted: true },
          { userId: id, friendId: user.id, accepted: true },
        ],
      },
    });
    if (!existingFriend) {
      return res.status(400).send({ error: 'No friend request found' });
    }
    const updatedFriend = await this.prisma.friend.deleteMany({
      where: {
        OR: [
          { userId: user.id, friendId: id },
          { userId: id, friendId: user.id },
        ],
      },
    });
    if (!updatedFriend) {
      return res.status(400).send({ error: 'Failed to remove friend' });
    }
    return res.status(200).json({ success: true, msg: 'User removed!' });
  }
}
