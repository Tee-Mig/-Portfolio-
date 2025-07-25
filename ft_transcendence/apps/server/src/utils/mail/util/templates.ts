import { mailTemplates } from '../types';

export async function getTemplate<
  TemplateId extends keyof typeof mailTemplates,
>({
  templateId,
  context,
}: {
  templateId: TemplateId;
  context: Parameters<(typeof mailTemplates)[TemplateId]>[0];
}) {
  const template = mailTemplates[templateId];
  const email = mailTemplates[templateId](context);
  const subject = template.Subject;
  const html = email;
  const text = email;
  return { html, text, subject };
}
