import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as cookieParser from 'cookie-parser';

async function bootstrap() {
  const app = await NestFactory.create(AppModule, { abortOnError: false });
  app.enableCors({
    origin: '*',
    credentials: true,
  });
  app.use(cookieParser());
  app.enableShutdownHooks();
  await app.listen(process.env.PORT || 8000);
}

bootstrap();
