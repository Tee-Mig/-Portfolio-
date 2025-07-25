/* eslint-disable @typescript-eslint/no-unsafe-assignment */
import { send } from '../provider';
import { getTemplate } from './templates';
import type { mailTemplates } from '../types';
import { z } from 'zod';

const ZSendEmailProps = z
  .string()
  .email()
  .min(1)
  .max(255)
  .transform((v) => v.toLowerCase());

export async function sendEmail<
  TemplateId extends keyof typeof mailTemplates,
>(params: {
  to: z.infer<typeof ZSendEmailProps>;
  templateId: TemplateId;
  context: Parameters<(typeof mailTemplates)[TemplateId]>[0];
}) {
  const { to, templateId, context } = params;

  const { html, text, subject } = await getTemplate({ templateId, context });

  try {
    // send the email
    await send({
      to,
      subject,
      text,
      html,
    });
    return true;
  } catch (e) {
    console.error(e);
    return false;
  }
}
