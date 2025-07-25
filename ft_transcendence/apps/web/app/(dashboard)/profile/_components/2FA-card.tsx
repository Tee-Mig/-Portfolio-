"use client";

import { Button } from "@web/components/ui/button";
import {
	Form,
	FormControl,
	FormDescription,
	FormField,
	FormItem,
	FormLabel,
	FormMessage,
} from "@web/components/ui/form"
import { Input } from "@web/components/ui/input"
import { Switch } from "@web/components/ui/switch"
import { Card } from "@web/components/card/card";
import * as z from "zod";
import { zodResolver } from "@hookform/resolvers/zod"
import { set, useForm } from "react-hook-form";
import { toast } from "sonner";
import { fetcher } from "@web/utils/fetcher";
import { User } from "@web/types/types";
import { KeyedMutator } from "swr";
import { useState } from "react";
import OTPAlert from "./alert";
import { useRouter } from 'next/navigation'

export function FACard({ user, mutate }: { user: User; mutate: KeyedMutator<any> }) {
	const router = useRouter()
	const [open, setOpen] = useState(false);
	const [email, setEmail] = useState("");
	const [tfaEnabled, setTfaEnabled] = useState(false);

	const formSchema = z.object({
		email: z.string().regex(/^.+@.+\..+$/, {
			message: "Please enter a valid email address.",
		}),
		enabled: z.boolean(),
	})

	// 1. Define your form.
	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			email: user.email,
			enabled: user.tfaEnabled,
		},
	})

	// 2. Define a submit handler.
	async function onSubmit(values: z.infer<typeof formSchema>) {
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		if (values.email == user.email && values.enabled == user.tfaEnabled) return;
		const data = await fetcher("/user/2fa", "POST", {
			email: values.email,
			tfaEnabled: values.enabled,
		});
		if (data.status != 200) {
			form.setError("enabled", {
				message: data.json.error,
			})
			toast.error(data.json.error);
			return;
		} else {
			if (data.json.otp) {
				setEmail(values.email);
				setTfaEnabled(values.enabled);
				setOpen(true);
				return;
			}
			toast.success("Email Updated.");
			mutate();
			router.refresh();
		}
	}

	return (
		<Card>
			<OTPAlert open={open} setOpen={setOpen} email={user.email} newEmail={email} tfaEnabled={tfaEnabled} />
			<Form {...form}>
				<form onSubmit={form.handleSubmit(onSubmit)}>
					<div className="p-6">
						<div className="flex items-center">
							<h4 className="text-2xl font-semibold text-white">
								2FA
							</h4>
							<FormField
								control={form.control}
								name="enabled"
								render={({ field }) => (
									<FormItem>
										<FormControl>
											<Switch className="ml-4" checked={field.value} onCheckedChange={field.onChange} />
										</FormControl>
										<FormMessage />
									</FormItem>
								)}
							/>
						</div>
						<p className="my-3 dark:text-gray-300">
							This is the email address where we will send your 2FA codes.
						</p>
						<FormField
							control={form.control}
							name="email"
							render={({ field }) => (
								<FormItem>
									<FormControl>
										<Input placeholder={user.email || "email@example.com"} {...field} autoComplete="off" className="max-w-md border-gray-700 bg-gray-900" />
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
					</div>
					<footer className="min-h-[57px] border-t-[1px] border-gray-700 py-3 px-6">
						<div className="flex items-center">
							<div>
								<p className="dark:text-gray-400">
									This will add a verification step after login.
								</p>
							</div>
							<div className="m-auto mr-0">
								<Button size="sm" className="h-8 font-medium" type="submit">
									Save
								</Button>
							</div>
						</div>
					</footer>
				</form>
			</Form>
		</Card>
	)
}
