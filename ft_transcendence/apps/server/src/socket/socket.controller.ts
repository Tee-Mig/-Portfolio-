import { OnModuleInit } from '@nestjs/common';
import { WebSocketGateway, WebSocketServer } from '@nestjs/websockets';
import { Server } from 'socket.io';
import { PrismaService } from '@server/prisma/prisma.service';
import { AuthService } from '@server/auth/auth.service';

@WebSocketGateway({
  path: '/socket',
  cors: {
    origin: process.env.FRONT_URL || 'http://localhost:3000',
    exposedHeaders: ['Authorization'],
    credentials: true,
    allowedHeaders: ['Authorization'],
  },
})
export class SocketController implements OnModuleInit {
  @WebSocketServer()
  server: Server;

  constructor(
    private prisma: PrismaService,
    private authService: AuthService,
  ) {}

  onModuleInit() {
    this.server.on('connection', async (socket) => {
      if (!socket.handshake.auth || !socket.handshake.auth.token) {
        return socket.disconnect();
      }

      if (
        !(await this.authService.isLoggedInFromToken(
          socket.handshake.auth.token,
        ))
      ) {
        return socket.disconnect();
      }
      const user = await this.authService.getLoggedInUserFromToken(
        socket.handshake.auth.token,
      );
      if (!user) {
        return socket.disconnect();
      }

      await this.prisma.user.update({
        where: { id: user.id },
        data: { status: 'online', inGame: false },
      });

      socket.emit('user', user);

      socket.on('path', async (data: { path: string }) => {
        const path =
          data.path.split('/').length > 1 ? data.path.split('/')[1] : data.path;
        await this.prisma.user.update({
          where: { id: user.id },
          data: { status: `online - on ${path}` },
        });
      });

      socket.on('disconnect', async () => {
        try {
          await this.prisma.user.update({
            where: { id: user.id },
            data: { status: 'offline', inGame: false },
          });
        } catch (e) {}
      });
    });
  }
}
