import { Module } from '@nestjs/common';
import { ScheduleModule } from '@nestjs/schedule';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { ConfigModule } from '@nestjs/config';
import { AuthModule } from './auth/auth.module';
import { PrismaModule } from './prisma/prisma.module';
import { UserModule } from './user/user.module';
import { FriendModule } from './friend/friend.module';
import { ChatModule } from './chat/chat.module';
import { GatewayModule } from './gateway/gateway.module';
import { SocketModule } from './socket/socket.module';
import { APP_FILTER } from '@nestjs/core';
import InternalServerErrorExceptionFilter from './filter/http-exception.filter';

@Module({
  imports: [
    ConfigModule.forRoot(),
    ScheduleModule.forRoot(),
    AuthModule,
    PrismaModule,
    UserModule,
    FriendModule,
    ChatModule,
    GatewayModule,
    SocketModule,
  ],
  controllers: [AppController],
  providers: [
    AppService,
    {
      provide: APP_FILTER,
      useClass: InternalServerErrorExceptionFilter,
    },
  ],
})
export class AppModule {}
