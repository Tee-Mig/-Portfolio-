import { z } from 'zod';

const ZNewUserProps = z.object({
  token: z.string(),
});

export function NewUser({ token }: z.infer<typeof ZNewUserProps>) {
  return `<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"><div><h1>Welcome to Pungy</h1><p>Enter the following OTP to verify your account</p><p>${token}</p><br /><br><br><p>If you did not request this email you can safely ignore it.</p></div>`;
}

NewUser.Subject = `OTP Code - Pungy`;
