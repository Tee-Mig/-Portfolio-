import { Injectable, Logger } from '@nestjs/common';
import { Cron } from '@nestjs/schedule';
import { PrismaService } from './prisma/prisma.service';

@Injectable()
export class AppService {
  private readonly logger = new Logger(AppService.name);
  constructor(private prisma: PrismaService) {}

  getHello(): string {
    return 'Hello Tom!';
  }

  @Cron('0 * * * * *')
  async handleCron() {
    const res = await this.prisma.muted.deleteMany({
      where: {
        createdAt: {
          // 10 min ago
          lte: new Date(Date.now() - 1000 * 60 * 10),
        },
      },
    });
    this.logger.debug(
      'Muted users older than 10 minutes have been cleared. Count: ' +
        res.count,
    );
  }
}
