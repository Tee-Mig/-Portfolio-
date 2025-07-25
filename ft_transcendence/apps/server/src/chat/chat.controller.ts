import { Controller, Get, Post, Req, Res } from '@nestjs/common';
import { AuthService } from '@server/auth/auth.service';
import { PrismaService } from '@server/prisma/prisma.service';
import { Request, Response } from 'express';
import { z } from 'zod';
import * as bcrypt from 'bcrypt';
import { FriendService } from '@server/friend/friend.service';
import { env } from 'process';

const userFilter = {
  id: true,
  username: true,
  pfp: true,
  status: true,
  inGame: true,
  createdAt: true,
  updatedAt: true,
};

@Controller('chat')
export class ChatController {
  constructor(
    private prisma: PrismaService,
    private authService: AuthService,
    private friendService: FriendService,
  ) {}

  @Get('all')
  async getAllChats(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const u = await this.prisma.user.findUnique({
      where: {
        id: user.id,
      },
      include: {
        blocked: true,
      },
    });

    if (!u) {
      return res.status(400).send({ error: 'No user found' });
    }

    const chats = await this.prisma.chat.findMany({
      where: {
        users: {
          some: {
            id: user.id,
          },
        },
        banned: {
          none: {
            id: user.id,
          },
        },
        NOT: {
          type: 'private',
          users: {
            some: {
              id: {
                in: u.blocked.map((b: any) => b.blockedUser_id),
              },
            },
          },
        },
      },
      include: {
        messages: {
          select: {
            id: true,
            content: true,
            author: {
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
            createdAt: true,
          },
          orderBy: {
            createdAt: 'desc',
          },
          take: 1,
        },
        users: {
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

    for (const chat of chats) {
      chat.password = '';
    }

    return res.status(200).json(chats);
  }

  @Get(':id/:password?')
  async getChat(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.coerce.number().min(0),
      password: z.string().optional(),
    });
    if (!schema.safeParse(req.params).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id, password } = schema.parse(req.params);

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

    const chat: any = await this.prisma.chat.findFirst({
      where: {
        id: id,
      },
      include: {
        messages: {
          where: {
            NOT: {
              author: {
                id: {
                  in: blockedUsers.map((u: any) => u.blockedUser.id),
                },
              },
            },
          },
          select: {
            id: true,
            content: true,
            isInvite: true,
            joinLink: true,
            watchLink: true,
            author: {
              select: userFilter,
            },
            createdAt: true,
          },
        },
        users: {
          select: userFilter,
        },
        owner: {
          select: userFilter,
        },
        admins: {
          select: userFilter,
        },
        banned: {
          select: userFilter,
        },
        muted: {
          select: {
            user: {
              select: userFilter,
            },
          },
        },
      },
    });

    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (chat.banned.some((bannedUser: any) => bannedUser.id === user.id)) {
      return res.status(423).send({ error: 'You are banned from this chat' });
    }

    const isUserInChat = chat.users.some((u: any) => u.id === user.id);
    if (chat.type === 'private' && !isUserInChat) {
      return res
        .status(403)
        .send({ error: 'You are not in this private chat' });
    }

    if (!isUserInChat && chat.type === 'protected' && chat.password) {
      if (!password) {
        return res.status(403).send({ error: 'Incorrect password' });
      }
      if (!(await bcrypt.compare(password, chat.password))) {
        return res.status(403).send({ error: 'Incorrect password' });
      }
    }

    if (!isUserInChat) {
      await this.prisma.chat.update({
        where: {
          id: chat.id,
        },
        data: {
          users: {
            connect: {
              id: user.id,
            },
          },
        },
      });
    }

    let isMuted = false;
    for (const mutedUser of chat.muted) {
      if (mutedUser.user.id === user.id) {
        isMuted = true;
        break;
      }
    }

    for (const message of chat.messages) {
      message.author = {
        ...message.author,
        isFromUser: message.author.id === user.id,
      };
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

    const friends = await this.friendService.getAllFriendsTypes(user.id);
    const newUsers = [];
    for (const u of users) {
      if (!u) continue;
      if (user.id === u.id) continue;
      let isFriend = false;
      for (const friend of friends.friends) {
        if (!friend) continue;
        if (friend.id === user.id) {
          isFriend = true;
          break;
        }
      }
      newUsers.push({ ...u, isFriend: isFriend });
    }
    return res.status(200).json({
      ...chat,
      allUsers: newUsers,
      user: user,
      muted: isMuted,
      isOwner: chat.ownerId === user.id,
      isAdmin: chat.admins.some((admin: any) => admin.id === user.id),
    });
  }

  @Post('send')
  async sendMessage(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.number().min(0),
      content: z.string().min(1),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id, content } = schema.parse(req.body);

    const chat = await this.prisma.chat.findFirst({
      where: {
        id: id,
        banned: {
          none: {
            id: user.id,
          },
        },
      },
      include: {
        users: {
          select: {
            id: true,
          },
        },
        muted: {
          select: {
            userId: true,
          },
        },
      },
    });
    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (!chat.users.some((u: any) => u.id === user.id)) {
      return res.status(403).send({ error: 'You are not in this chat' });
    }

    if (chat.muted.some((mutedUser: any) => mutedUser.userId === user.id)) {
      return res.status(423).send({ error: 'You are muted from this chat' });
    }

    const msg = await this.prisma.message.create({
      data: {
        content: content,
        chatId: chat.id,
        userId: user.id,
      },
    });
    if (!msg) {
      return res.status(400).send({ error: 'Failed to send message' });
    }

    return res.status(200).json({
      success: true,
    });
  }

  @Post('create')
  async createChat(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      type: z.enum(['public', 'protected', 'private']),
      password: z.string().optional(),
      users: z.array(z.number()).min(1),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'Invalid data provided' });
    }
    const { type, password, users } = schema.parse(req.body);

    if (type === 'protected' && !password) {
      return res
        .status(400)
        .send({ error: 'Password must be set for Protected chat.' });
    }

    if (type === 'private' && (!users || users.length === 0)) {
      return res
        .status(400)
        .send({ error: 'Please select at least one friend.' });
    }

    if (
      type === 'private' &&
      users &&
      users.some((u: number) => u === user.id)
    ) {
      return res
        .status(400)
        .send({ error: 'You cannot create a private chat with yourself.' });
    }

    if (type === 'private' && users && users.length > 1) {
      return res.status(400).send({
        error: 'You cannot create a private chat with multiple users.',
      });
    }

    if (type === 'private' && !users) {
      return res.status(400).send({
        error: 'You cannot be alone in a private chat.',
      });
    }

    const p =
      type === 'protected' && password ? await bcrypt.hash(password, 10) : '';
    const u = users
      ? users.map((u: number) => {
          return { id: u };
        })
      : [];
    u.push({ id: user.id });

    const chat = await this.prisma.chat.create({
      data: {
        type: type,
        password: p,
        ownerId: user.id,
        users: {
          connect: u,
        },
      },
    });

    return res.status(200).json({
      success: true,
      id: chat.id,
    });
  }

  @Post('update')
  async updateChat(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.number().min(0),
      type: z.enum(['public', 'protected', 'private']),
      password: z.string().optional(),
      users: z.array(z.coerce.number()).min(1),
      admins: z.array(z.coerce.number().optional()),
      owner: z.coerce.number(),
      banned: z.array(z.coerce.number().optional()),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'Invalid data provided' });
    }

    const { id, type, password, users, admins, owner, banned } = schema.parse(
      req.body,
    );

    if (
      !users ||
      users.length === 0 ||
      (users.length === 1 && users.some((u: number) => u === user.id))
    ) {
      return res
        .status(400)
        .send({ error: 'Please select at least one friend.' });
    }

    if (
      type === 'private' &&
      users &&
      users.length === 1 &&
      users.some((u: number) => u === user.id)
    ) {
      return res.status(400).send({
        error: 'You cannot create a private chat with only yourself.',
      });
    }

    if (type === 'private' && users && users.length > 2) {
      return res.status(400).send({
        error: 'You cannot create a private chat with multiple users.',
      });
    }

    const chat: any = await this.prisma.chat.findFirst({
      where: {
        id: id,
      },
      include: {
        messages: {
          select: {
            id: true,
            content: true,
            author: {
              select: userFilter,
            },
            createdAt: true,
          },
        },
        users: {
          select: userFilter,
        },
        owner: {
          select: userFilter,
        },
        admins: {
          select: userFilter,
        },
        banned: {
          select: userFilter,
        },
        muted: {
          select: {
            user: {
              select: userFilter,
            },
          },
        },
      },
    });

    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (
      !(
        chat.ownerId === user.id ||
        chat.admins.some((a: any) => a.id === user.id)
      )
    ) {
      return res
        .status(403)
        .send({ error: 'You do not have permission to do that' });
    }

    if (password && password != '' && chat.ownerId !== user.id) {
      return res
        .status(403)
        .send({ error: 'You do not have permission to change the password' });
    }

    if (chat.type !== 'protected' && type === 'protected' && !password) {
      return res
        .status(400)
        .send({ error: 'Password must be set for Protected chat.' });
    }

    if (type === 'private' && !users) {
      return res.status(400).send({
        error: 'You cannot be alone in a private chat.',
      });
    }

    if (owner != chat.ownerId && chat.ownerId !== user.id) {
      return res
        .status(403)
        .send({ error: 'You do not have permission to change the owner' });
    }

    if (banned && banned.some((u: number) => u === chat.ownerId)) {
      return res.status(403).send({ error: 'You cannot ban the owner' });
    }

    if (banned && banned.some((u: number) => u === user.id)) {
      return res.status(403).send({ error: 'You cannot ban yourself' });
    }

    if (
      users &&
      users.some((u: number) => chat.banned.some((b: any) => b.id === u))
    ) {
      return res.status(403).send({ error: 'You cannot add a banned user' });
    }

    if (
      banned &&
      banned.length > chat.banned.length &&
      !banned.some((u: number) => chat.banned.some((b: any) => b.id === u))
    ) {
      return res.status(403).send({ error: 'You cannot ban user from here' });
    }

    const payload: any = {
      type: type,
      password: chat.password,
      users: chat.users,
      admins: chat.admins,
      owner: chat.ownerId,
      banned: chat.banned,
    };

    if (type === 'protected' && password && password != '') {
      payload.password = await bcrypt.hash(password, 10);
    }

    payload.users = users
      ? users.map((u: number) => {
          return { id: u };
        })
      : [];
    if (payload.users && !payload.users.some((u: any) => u.id === user.id)) {
      payload.users.push({ id: user.id });
    }

    if (admins) {
      payload.admins = admins.map((u: number) => {
        return { id: u };
      });
    }

    if (owner && chat.ownerId === user.id) {
      payload.owner = owner;
    }

    if (banned) {
      payload.banned = banned.map((u: number) => {
        return { id: u };
      });
    }

    const updatedChat = await this.prisma.chat.update({
      where: {
        id: chat.id,
      },
      data: {
        type: payload.type,
        password: payload.password,
        users: {
          set: payload.users,
        },
        admins: {
          set: payload.admins,
        },
        ownerId: {
          set: payload.owner,
        },
        banned: {
          set: payload.banned,
        },
      },
    });

    return res.status(200).json({
      ...updatedChat,
      success: true,
    });
  }

  @Post('leave')
  async leaveChat(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'Invalid data provided' });
    }

    const { id } = schema.parse(req.body);

    const chat = await this.prisma.chat.findFirst({
      where: {
        id: id,
      },
      include: {
        users: {
          select: {
            id: true,
          },
        },
      },
    });

    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (chat.ownerId === user.id) {
      return res.status(403).send({ error: 'You cannot leave a chat you own' });
    }

    await this.prisma.chat.update({
      where: {
        id: chat.id,
      },
      data: {
        users: {
          disconnect: {
            id: user.id,
          },
        },
        admins: {
          disconnect: {
            id: user.id,
          },
        },
      },
    });

    return res.status(200).json({
      success: true,
    });
  }

  @Post('ban')
  async banUser(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.coerce.number().min(0),
      userId: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'Invalid data provided' });
    }

    const { id, userId } = schema.parse(req.body);

    const chat = await this.prisma.chat.findFirst({
      where: {
        id: id,
      },
      include: {
        messages: {
          select: {
            id: true,
            content: true,
            author: {
              select: userFilter,
            },
            createdAt: true,
          },
        },
        users: {
          select: userFilter,
        },
        owner: {
          select: userFilter,
        },
        admins: {
          select: userFilter,
        },
        banned: {
          select: userFilter,
        },
        muted: {
          select: {
            user: {
              select: userFilter,
            },
          },
        },
      },
    });

    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (!chat.users.some((u: any) => u.id === userId)) {
      return res.status(400).send({ error: 'User not found in chat' });
    }

    if (
      user.id != chat.ownerId &&
      !chat.admins.some((a: any) => a.id === user.id)
    ) {
      return res
        .status(403)
        .send({ error: 'You do not have permission to do that' });
    }

    if (chat.ownerId === userId) {
      return res.status(403).send({ error: 'You cannot ban yourself' });
    }

    if (chat.ownerId === userId) {
      return res.status(403).send({ error: 'You cannot ban the owner' });
    }

    await this.prisma.chat.update({
      where: {
        id: chat.id,
      },
      data: {
        users: {
          disconnect: {
            id: userId,
          },
        },
        admins: {
          disconnect: {
            id: userId,
          },
        },
        banned: {
          connect: {
            id: userId,
          },
        },
      },
    });

    return res.status(200).json({
      success: true,
    });
  }

  @Post('kick')
  async kickUser(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.coerce.number().min(0),
      userId: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'Invalid data provided' });
    }

    const { id, userId } = schema.parse(req.body);

    const chat = await this.prisma.chat.findFirst({
      where: {
        id: id,
      },
      include: {
        messages: {
          select: {
            id: true,
            content: true,
            author: {
              select: userFilter,
            },
            createdAt: true,
          },
        },
        users: {
          select: userFilter,
        },
        owner: {
          select: userFilter,
        },
        admins: {
          select: userFilter,
        },
        banned: {
          select: userFilter,
        },
        muted: {
          select: {
            user: {
              select: userFilter,
            },
          },
        },
      },
    });

    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (!chat.users.some((u: any) => u.id === userId)) {
      return res.status(400).send({ error: 'User not found in chat' });
    }

    if (
      user.id != chat.ownerId &&
      !chat.admins.some((a: any) => a.id === user.id)
    ) {
      return res
        .status(403)
        .send({ error: 'You do not have permission to do that' });
    }

    if (chat.ownerId === userId) {
      return res.status(403).send({ error: 'You cannot kick yourself' });
    }

    if (chat.ownerId === userId) {
      return res.status(403).send({ error: 'You cannot kick the owner' });
    }

    await this.prisma.chat.update({
      where: {
        id: chat.id,
      },
      data: {
        users: {
          disconnect: {
            id: userId,
          },
        },
        admins: {
          disconnect: {
            id: userId,
          },
        },
      },
    });

    return res.status(200).json({
      success: true,
    });
  }

  @Post('mute')
  async muteUser(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.coerce.number().min(0),
      userId: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'Invalid data provided' });
    }

    const { id, userId } = schema.parse(req.body);

    const chat = await this.prisma.chat.findFirst({
      where: {
        id: id,
      },
      include: {
        messages: {
          select: {
            id: true,
            content: true,
            author: {
              select: userFilter,
            },
            createdAt: true,
          },
        },
        users: {
          select: userFilter,
        },
        owner: {
          select: userFilter,
        },
        admins: {
          select: userFilter,
        },
        banned: {
          select: userFilter,
        },
        muted: {
          select: {
            user: {
              select: userFilter,
            },
          },
        },
      },
    });

    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (!chat.users.some((u: any) => u.id === userId)) {
      return res.status(400).send({ error: 'User not found in chat' });
    }

    if (
      user.id != chat.ownerId &&
      !chat.admins.some((a: any) => a.id === user.id)
    ) {
      return res
        .status(403)
        .send({ error: 'You do not have permission to do that' });
    }

    if (chat.ownerId === userId) {
      return res.status(403).send({ error: 'You cannot mute yourself' });
    }

    if (chat.ownerId === userId) {
      return res.status(403).send({ error: 'You cannot mute the owner' });
    }

    await this.prisma.chat.update({
      where: {
        id: chat.id,
      },
      data: {
        muted: {
          connectOrCreate: {
            where: {
              id: userId,
            },
            create: {
              userId: userId,
            },
          },
        },
      },
    });

    return res.status(200).json({
      success: true,
    });
  }

  @Post('dm')
  async dmUser(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    console.log(req.body);

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }
    const schema = z.object({
      id: z.coerce.number().min(0),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { id } = schema.parse(req.body);

    if (id === user.id) {
      return res
        .status(400)
        .send({ error: 'You cannot create a private chat with yourself.' });
    }

    const u = await this.prisma.user.findUnique({
      where: {
        id: id,
      },
    });

    if (!u) {
      return res.status(400).send({ error: 'No user found' });
    }

    let chat = await this.prisma.chat.findFirst({
      where: {
        type: 'private',
        users: {
          some: {
            id: user.id,
          },
        },
        AND: {
          type: 'private',
          users: {
            some: {
              id: id,
            },
          },
        },
      },
    });

    if (!chat) {
      chat = await this.prisma.chat.create({
        data: {
          type: 'private',
          password: '',
          ownerId: user.id,
          users: {
            connect: [
              {
                id: user.id,
              },
              {
                id: id,
              },
            ],
          },
        },
      });
    }

    return res.status(200).json({
      success: true,
      url: `${process.env.FRONT_URL}/chat/${chat.id}`,
    });
  }

  @Post('game/invite')
  async gameInvite(@Req() req: Request, @Res() res: Response) {
    if (!(await this.authService.isLoggedIn(req))) {
      return res.status(401).json({ error: 'forbidden' });
    }

    const user = await this.authService.getLoggedInUser(req);
    if (!user) {
      return res.status(400).send({ error: 'No user found' });
    }

    const schema = z.object({
      chatID: z.coerce.number().min(0),
      inviteCode: z.string().min(1),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).send({ error: 'No/Invalid id provided' });
    }
    const { chatID, inviteCode } = schema.parse(req.body);

    const chat = await this.prisma.chat.findFirst({
      where: {
        id: chatID,
        banned: {
          none: {
            id: user.id,
          },
        },
        users: {
          some: {
            id: user.id,
          },
        },
      },
      include: {
        users: {
          select: {
            id: true,
          },
        },
        banned: {
          select: {
            id: true,
          },
        },
      },
    });
    if (!chat) {
      return res.status(400).send({ error: 'No chat found' });
    }

    if (!chat.users.some((u: any) => u.id === user.id)) {
      return res.status(403).send({ error: 'You are not in this chat' });
    }

    if (chat.banned.some((bannedUser: any) => bannedUser.id === user.id)) {
      return res.status(423).send({ error: 'You are banned from this chat' });
    }

    const msg = await this.prisma.message.create({
      data: {
        content: `I have invited you to play a game! Code: ${inviteCode}`,
        chatId: chat.id,
        userId: user.id,
        isInvite: true,
        joinLink: `${env.FRONT_URL}/game/join/${inviteCode}`,
        watchLink: `${env.FRONT_URL}/game/watch/${inviteCode}`,
      },
    });

    if (!msg) {
      return res.status(400).send({ error: 'Failed to send invite' });
    }

    return res.status(200).json({
      success: true,
    });
  }
}
