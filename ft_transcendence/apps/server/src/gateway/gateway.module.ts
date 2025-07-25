import { Module } from '@nestjs/common';
import { AuthService } from '@server/auth/auth.service';
import { MyGateway } from '@server/gateway/gateway.controller';
import { PrismaModule } from '@server/prisma/prisma.module';

@Module({
  imports: [PrismaModule],
  controllers: [],
  providers: [AuthService, MyGateway],
})
export class GatewayModule {}
