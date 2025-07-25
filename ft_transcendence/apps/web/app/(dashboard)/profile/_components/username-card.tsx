"use client";

import { Button } from "@web/components/ui/button";
import {
	Form,
	FormControl,
	FormField,
	FormItem,
	FormMessage,
} from "@web/components/ui/form"
import { Input } from "@web/components/ui/input"
import { Card } from "@web/components/card/card";
import * as z from "zod";
import { zodResolver } from "@hookform/resolvers/zod"
import { useForm } from "react-hook-form";
import { fetcher } from "@web/utils/fetcher";
import { toast } from "sonner";
import { KeyedMutator } from "swr";
import { User } from "@web/types/types";

export function UsernameCard({ user, mutate }: { user: User; mutate: KeyedMutator<any> }) {
	const formSchema = z.object({
		username: z.string().min(1, {
			message: "Username must be at least 1 characters.",
		}).max(20, {
			message: "Username must be at most 20 characters.",
		}).regex(/^[a-zA-Z0-9_]+$/, {
			message: "Username must only contain letters, numbers, and underscores.",
		}),
	})

	// 1. Define your form.
	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			username: user.username,
		},
	})

	// 2. Define a submit handler.
	async function onSubmit(values: z.infer<typeof formSchema>) {
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		const data = await fetcher("/user/username", "POST", {
			username: values.username,
		});
		if (data.status != 200) {
			form.setError("username", {
				message: data.json.error,
			})
			return;
		} else {
			toast.success("Username updated.");
			mutate();
		}
	}

	return (
		<Card>
			<Form {...form}>
				<form onSubmit={form.handleSubmit(onSubmit)}>
					<div className="p-6">
						<h4 className="text-2xl font-semibold text-white">Username</h4>
						<p className="my-3 dark:text-gray-300">
							This is your public display name.
						</p>
						<FormField
							control={form.control}
							name="username"
							render={({ field }) => (
								<FormItem>
									<FormControl>
										<Input placeholder={user.username || "example"} {...field} autoComplete="off" className="max-w-md border-gray-700 bg-gray-900" />
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
									Please use 20 characters at maximum.
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
