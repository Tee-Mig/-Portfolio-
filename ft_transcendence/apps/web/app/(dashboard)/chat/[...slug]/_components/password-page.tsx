"use client";


import { Button } from "@web/components/ui/button";
import { Input } from "@web/components/ui/input"
import {
	Form,
	FormControl,
	FormField,
	FormItem,
	FormLabel,
	FormMessage,
	FormDescription,
} from "@web/components/ui/form"
import { zodResolver } from "@hookform/resolvers/zod"
import { useForm } from "react-hook-form"
import * as z from "zod"
import { useRouter } from 'next/navigation'

const formSchema = z.object({
	password: z.string().min(1, {
		message: "Password must have at least 1 characters.",
	}),
})

export default function PasswordLock({ error, data, chatID }: { error: any, data: any, chatID: string }) {
	const router = useRouter()
	// 1. Define your form.
	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			password: "",
		},
	})

	// 2. Define a submit handler.
	function onSubmit(values: z.infer<typeof formSchema>) {
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		router.push(`/chat/${chatID}/${values.password}`)
	}

	return (
		<div>
			<div>
				<p className="text-red-500">
					{data && data.error ? data.error : (
						<pre>{JSON.stringify(data, null, 2)}</pre>
					)}
				</p>
				{error && (
					<pre>
						{JSON.stringify(error, null, 2)}
					</pre>
				)}
			</div>
			{data && data.error && data.error === "Incorrect password" && <Form {...form}>
				<form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
					<FormField
						control={form.control}
						name="password"
						render={({ field }) => (
							<FormItem>
								<FormLabel>Password</FormLabel>
								<FormControl>
									<Input type="password" placeholder="•••" {...field} />
								</FormControl>
								<FormDescription>
									Enter the password to unlock this chat.
								</FormDescription>
								<FormMessage />
							</FormItem>
						)}
					/>
					<Button type="submit">Submit</Button>
				</form>
			</Form>}
		</div>
	)
}