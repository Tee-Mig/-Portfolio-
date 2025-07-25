import { Module } from '@nestjs/common';
import { ChatController } from './chat.controller';
import { AuthService } from '@server/auth/auth.service';
import { PrismaModule } from '@server/prisma/prisma.module';
import { FriendService } from '@server/friend/friend.service';

@Module({
  imports: [PrismaModule],
  controllers: [ChatController],
  providers: [AuthService, FriendService],
})
export class ChatModule {}
