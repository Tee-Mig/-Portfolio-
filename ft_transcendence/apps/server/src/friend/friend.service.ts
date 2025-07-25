import { Injectable } from '@nestjs/common';
import { PrismaService } from '@server/prisma/prisma.service';

@Injectable()
export class FriendService {
  constructor(private prisma: PrismaService) {}

  async getAllFriendsTypes(userId: number) {
    const rawFriends = await this.prisma.friend.findMany({
      where: {
        OR: [{ friendId: userId }, { userId: userId }],
      },
      include: {
        friend: {
          select: {
            id: true,
            username: true,
            pfp: true,
            status: true,
            inGame: true,
            createdAt: true,
            updatedAt: true,
          },
        },
        user: {
          select: {
            id: true,
            username: true,
            pfp: true,
            status: true,
            inGame: true,
            createdAt: true,
            updatedAt: true,
          },
        },
      },
    });
    if (!rawFriends) {
      return {
        friends: [],
        pending: [],
        sent: [],
      };
    }

    const acceptedFriends = rawFriends.map((friend) => {
      if (friend.accepted) {
        if (friend.userId === userId) {
          return friend.friend;
        } else {
          return friend.user;
        }
      }
    });
    const pendingFriendRequests = rawFriends.map((friend) => {
      if (!friend.accepted) {
        if (friend.friendId === userId) {
          return friend.user;
        }
      }
    });

    const sentFriendRequests = rawFriends.map((friend) => {
      if (!friend.accepted) {
        if (friend.userId === userId) {
          return friend.friend;
        }
      }
    });

    return {
      friends: acceptedFriends.filter((friend) => friend !== undefined),
      pending: pendingFriendRequests.filter((friend) => friend !== undefined),
      sent: sentFriendRequests.filter((friend) => friend !== undefined),
    };
  }
}
