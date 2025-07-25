import { PrismaClient, User } from '@prisma/client';
const prisma = new PrismaClient();
import { faker } from '@faker-js/faker';

const userAmount = 10;

async function main() {
  console.log(`Starting to seed DB...`);
  for (let i = 0; i < userAmount; i++) {
    const user: User = await prisma.user.create({
      data: {
        id42: faker.number.int({ max: 10000000 }),
        username: faker.internet.userName(),
        email: faker.internet.email(),
      },
    });
    console.log(`Created user with id: ${user.id}`);
  }
  console.log(`Seeding finished.`);
}

main()
  .catch((e) => console.error(e))
  .finally(async () => {
    console.log('Seeding complete.');
    await prisma.$disconnect();
  });
