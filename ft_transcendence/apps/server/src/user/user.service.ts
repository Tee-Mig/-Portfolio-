import { Injectable } from '@nestjs/common';
import { PrismaService } from '@server/prisma/prisma.service';

@Injectable()
export class UserService {
  constructor(private prisma: PrismaService) {}

  async getRankings() {
    const games = await this.prisma.game.findMany({});

    const playersWins: { [key: string]: number } = games.reduce(
      (acc: { [key: string]: number }, game) => {
        const winner = game.winnerId.toString();
        if (!acc[winner]) {
          acc[winner] = 0;
        }
        acc[winner] += 1;
        return acc;
      },
      {},
    );

    const ranking: { id: string; wins: number }[] = [];
    for (const [id, wins] of Object.entries(playersWins)) {
      ranking.push({ id, wins });
    }

    ranking.sort((a, b) => b.wins - a.wins);

    return ranking;
  }

  async getRanking(id: number) {
    const ranking = await this.getRankings();

    const rank = ranking.findIndex((player) => player.id === id.toString()) + 1;

    return rank;
  }
}
