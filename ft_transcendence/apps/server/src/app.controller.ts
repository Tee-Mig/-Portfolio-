import { Controller, Get, Res, UseFilters } from '@nestjs/common';
import { AppService } from './app.service';
import { Response } from 'express';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get('/hello')
  getHello(@Res() res: Response) {
    return res.status(200).send('Hello World!');
  }
}
