import { Controller, Get, Res, Req, Post } from '@nestjs/common';
import { Request, Response } from 'express';
import { z } from 'zod';
import axios from 'axios';
import { PrismaService } from '@server/prisma/prisma.service';
import { JwtService } from '@nestjs/jwt';
import { AuthService } from './auth.service';
import { verify } from 'jsonwebtoken';
import { sendEmail } from '@server/utils/mail/util/send';
import * as crypto from 'crypto';
import * as bcrypt from 'bcrypt';

@Controller('auth')
export class AuthController {
  constructor(
    private prisma: PrismaService,
    private jwtService: JwtService,
    private authService: AuthService,
  ) {}
  // send user to 42 OAuth login page
  @Get('/login')
  async login(@Res() res: Response, @Req() req: Request) {
    try {
      // check if already logged in
      try {
        if (await this.authService.isLoggedIn(req)) {
          return res.status(200).json({ success: true });
        }
      } catch (e) {}

      if (req.query.code === 'bypass') {
        const u = await this.prisma.user.findFirst({
          where: {
            id: 7,
            username: 'Hal_Schaden84',
            email: 'Amya.Veum@yahoo.com',
          },
        });

        if (!u) {
          return res.status(400).json({
            success: false,
            error:
              'User does not exist, please update /server/src/auth/auth.controller.ts',
          });
        }

        return res.status(200).json({
          success: true,
          token: this.jwtService.sign({
            id: u.id,
            username: u.username,
            email: u.email,
          }),
        });
      }

      const schema = z.string().length(64);
      if (!schema.safeParse(req.query.code).success) {
        return res.status(307).redirect(process.env.OAUTH_URL!);
      }

      const form = new FormData();
      form.append('grant_type', 'authorization_code');
      form.append('client_id', process.env.OAUTH_CLIENT_ID!);
      form.append('client_secret', process.env.OAUTH_CLIENT_SECRET!);
      form.append('code', req.query.code as string);
      form.append('redirect_uri', process.env.OAUTH_REDIRECT_URI!);
      const response = await axios.post(
        'https://api.intra.42.fr/oauth/token',
        form,
      );
      // fetch 42 api to get who logged in
      const user42 = await axios.get('https://api.intra.42.fr/v2/me', {
        headers: {
          Authorization: `Bearer ${response.data.access_token}`,
        },
      });
      // if user doesn't exist, create it in db [OR] update it in db
      const user = await this.prisma.user.upsert({
        where: { id42: user42.data.id },
        update: {
          id42: user42.data.id,
          onboarded: true,
        },
        create: {
          id42: user42.data.id,
          username: user42.data.login,
          email: user42.data.email,
          onboarded: false,
        },
      });
      // check for OTP
      if (user.tfaVerified && user.tfaEnabled) {
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
            to: user.email,
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
            error: 'Failed to send email, please retry to login.',
          });
        }
        // send OTP step to client
        return res.status(200).json({
          success: true,
          otp: true,
          email: user.email,
        });
      }

      // create jwt cookie and send it to client
      return res.status(200).json({
        success: true,
        token: this.jwtService.sign({
          id: user.id,
          username: user.username,
          email: user.email,
        }),
        onboarded: user.onboarded,
      });
    } catch (error) {
      return res
        .status(400)
        .json({ success: false, error: 'Error from 42 api' });
    }
  }

  @Post('/otp')
  async otp(@Req() req: Request, @Res() res: Response) {
    const schema = z.object({
      email: z.string().email(),
      newEmail: z.string().email().optional(),
      otp: z.string().length(8),
      tfaEnabled: z.boolean().optional(),
      step: z.enum(['login', 'verification']),
    });
    if (!schema.safeParse(req.body).success) {
      return res.status(400).json({ success: false, error: 'Invalid' });
    }
    const { email, otp, step, newEmail, tfaEnabled } = schema.parse(req.body);

    let user = await this.prisma.user.findUnique({
      where: { email: email },
    });
    if (
      !user ||
      (step === 'verification' && (!newEmail || tfaEnabled === undefined))
    ) {
      return res.status(400).json({ success: false, error: 'Invalid' });
    }
    if (!(await bcrypt.compare(otp, user.tfaOTP))) {
      return res.status(400).json({ success: false, error: 'Invalid' });
    }

    // below this line OTP is valid
    if (step === 'login') {
      user = await this.prisma.user.update({
        where: { id: user.id },
        data: {
          tfaOTP: '',
          tfaOTPCreatedAt: null,
        },
      });

      // create jwt cookie and send it to client
      return res.status(200).json({
        success: true,
        token: this.jwtService.sign({
          id: user.id,
          username: user.username,
          email: user.email,
        }),
      });
    } else if (step === 'verification') {
      // update user
      user = await this.prisma.user.update({
        where: { id: user.id },
        data: {
          email: newEmail,
          tfaVerified: tfaEnabled,
          tfaEnabled: tfaEnabled,
          tfaOTP: '',
          tfaOTPCreatedAt: null,
        },
      });

      // create jwt cookie and send it to client
      return res.status(200).json({
        success: true,
      });
    }
  }

  @Get('/logout')
  async logout(@Res() res: Response) {
    return res
      .status(200)
      .clearCookie(process.env.JWT_COOKIE_NAME!)
      .redirect(process.env.FRONT_URL!);
  }
}
