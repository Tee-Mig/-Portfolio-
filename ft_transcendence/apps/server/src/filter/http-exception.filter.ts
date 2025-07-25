//InternalServerError.filter.ts
import {
  InternalServerErrorException,
  Catch,
  ArgumentsHost,
  ExceptionFilter,
  HttpStatus,
  HttpException,
} from '@nestjs/common';
// catch all error
@Catch()
export default class InternalServerErrorExceptionFilter
  implements ExceptionFilter
{
  catch(exception: Error, host: ArgumentsHost) {
    const { message: errMsg, stack: errStack, name: errName } = exception;
    // let errRes = exception.getResponse();
    // let errCode = exception.getStatus();
    const ctx = host.switchToHttp();
    const req = ctx.getRequest();
    const res = ctx.getResponse();
    const statusName = '系统内部错误';
    res.statusCode = HttpStatus.INTERNAL_SERVER_ERROR;
    // HttpException Error
    if (exception instanceof HttpException) {
      // set httpException res to res
      res.status(exception.getStatus()).json(exception.getResponse());
      return;
    }
    // other error to rewirte InternalServerErrorException response
    res.status(400).json({
      sucess: false,
      error: 'Unknown error',
      message: 'Unknown error',
    });
  }
}
