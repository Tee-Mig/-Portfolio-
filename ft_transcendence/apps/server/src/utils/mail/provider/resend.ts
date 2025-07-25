import type { SendEmailHandler } from '../types';
import { Resend } from 'resend';

const resend = new Resend(process.env.RESEND_API_KEY);

export const send: SendEmailHandler = async ({ to, subject, html }) => {
  try {
    const res = await resend.emails.send({
      from: process.env.EMAIL_FROM!,
      to: to,
      subject: subject,
      html: html,
    });
    if (!res.data?.id) {
      throw new Error(JSON.stringify(res));
    }
  } catch (error) {
    console.error(error);
    throw new Error('Could not send email');
  }
};
