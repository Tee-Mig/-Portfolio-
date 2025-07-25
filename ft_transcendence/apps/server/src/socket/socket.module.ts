import { Module } from '@nestjs/common';
import { AuthService } from '@server/auth/auth.service';
import { PrismaModule } from '@server/prisma/prisma.module';
import { SocketController } from './socket.controller';

@Module({
  imports: [PrismaModule],
  controllers: [],
  providers: [AuthService, SocketController],
})
export class SocketModule {}
