import { Request } from 'express';
import { verify } from 'jsonwebtoken';
import { z } from 'zod';
import { Injectable, UnauthorizedException } from '@nestjs/common';
import { PrismaService } from '@server/prisma/prisma.service';

type PublicUser = {
  id: number;
  id42: number;
  email: string;
  username: string;
  pfp: string;
  status: string;
  tfaEnabled: boolean;
  tfaVerified: boolean;
  tfaOTP: string | null;
  inGame: boolean;
  createdAt: Date;
  updatedAt: Date;
};

@Injectable()
export class AuthService {
  constructor(private prisma: PrismaService) {}

  // check if user is logged in
  async isLoggedIn(req: Request): Promise<boolean> {
    try {
      const token = req.headers['authorization']?.split(' ')[1];
      if (token === undefined || token === '') return false;
      if (!token) throw new UnauthorizedException();

      const decoded: any = verify(token, process.env.JWT_SECRET!, {
        ignoreExpiration: true,
      });

      const schema = z.object({
        id: z.number(),
        username: z.string(),
        email: z.string(),
        iat: z.number().optional(),
        exp: z.number().optional(),
      });
      if (!schema.safeParse(decoded).success)
        throw new Error('wrong jwt schema');
      const user = await this.prisma.user.findUnique({
        where: { id: decoded.id },
      });
      if (!user) throw new Error('no user found');
      return true;
    } catch (e) {
      return false;
    }
  }

  async isLoggedInFromToken(token: string): Promise<boolean> {
    try {
      if (!token || token === '') throw new UnauthorizedException();

      const decoded: any = verify(token, process.env.JWT_SECRET!, {
        ignoreExpiration: true,
      });

      const schema = z.object({
        id: z.number(),
        username: z.string(),
        email: z.string(),
        iat: z.number().optional(),
        exp: z.number().optional(),
      });
      if (!schema.safeParse(decoded).success)
        throw new Error('wrong jwt schema');
      const user = await this.prisma.user.findUnique({
        where: { id: decoded.id },
      });
      if (!user) throw new Error('no user found');
      return true;
    } catch (e) {
      console.error(e);
      return false;
    }
  }

  async getLoggedInUser(req: Request): Promise<PublicUser | null> {
    try {
      const token = req.headers['authorization']?.split(' ')[1];
      if (!token || token === '') throw new UnauthorizedException();

      const decoded: any = verify(token, process.env.JWT_SECRET!, {
        ignoreExpiration: true,
      });

      const schema = z.object({
        id: z.number(),
        username: z.string(),
        email: z.string(),
        iat: z.number().optional(),
        exp: z.number().optional(),
      });
      if (!schema.safeParse(decoded).success)
        throw new Error('wrong jwt schema');
      const user = await this.prisma.user.findUnique({
        where: { id: decoded.id },
      });
      if (!user) throw new Error('no user found');
      return user;
    } catch (e) {
      console.error(e);
      return null;
    }
  }

  async getLoggedInUserFromToken(token: string): Promise<PublicUser | null> {
    try {
      if (!token || token === '') throw new UnauthorizedException();

      const decoded: any = verify(token, process.env.JWT_SECRET!, {
        ignoreExpiration: true,
      });

      const schema = z.object({
        id: z.number(),
        username: z.string(),
        email: z.string(),
        iat: z.number().optional(),
        exp: z.number().optional(),
      });
      if (!schema.safeParse(decoded).success)
        throw new Error('wrong jwt schema');
      const user = await this.prisma.user.findUnique({
        where: { id: decoded.id },
      });
      if (!user) throw new Error('no user found');
      return user;
    } catch (e) {
      console.error(e);
      return null;
    }
  }

  async getAllUsers(): Promise<PublicUser[] | null> {
    try {
      const users = await this.prisma.user.findMany();
      if (!users) throw new Error('no user found');
      return users;
    } catch (e) {
      console.error(e);
      return null;
    }
  }
}
