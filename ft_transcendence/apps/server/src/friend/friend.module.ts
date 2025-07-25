import { Module } from '@nestjs/common';
import { FriendController } from './friend.controller';
import { PrismaModule } from '@server/prisma/prisma.module';
import { AuthService } from '@server/auth/auth.service';

@Module({
  imports: [PrismaModule],
  controllers: [FriendController],
  providers: [AuthService],
})
export class FriendModule {}
