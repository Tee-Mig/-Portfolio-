import { NewUser } from './emails/newUser';

export interface SendEmailParams {
  to: string;
  subject: string;
  text?: string;
  html: string;
}

export type SendEmailHandler = (params: SendEmailParams) => Promise<void>;

export const mailTemplates = {
  newUser: NewUser,
};
