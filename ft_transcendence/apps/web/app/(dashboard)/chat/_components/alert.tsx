"use client";

import {
	AlertDialog,
	AlertDialogAction,
	AlertDialogCancel,
	AlertDialogContent,
	AlertDialogDescription,
	AlertDialogFooter,
	AlertDialogHeader,
	AlertDialogTitle,
	AlertDialogTrigger,
} from "@web/components/ui/alert-dialog"
import {
	Form,
	FormControl,
	FormDescription,
	FormField,
	FormItem,
	FormLabel,
	FormMessage,
} from "@web/components/ui/form"
import {
	Select,
	SelectContent,
	SelectItem,
	SelectTrigger,
	SelectValue,
} from "@web/components/ui/select"
import { zodResolver } from "@hookform/resolvers/zod"
import { useForm } from "react-hook-form"
import * as z from "zod"
import { Icon, MultiSelect, MultiSelectItem } from "@tremor/react";
import { Button } from "@web/components/ui/button";
import { Loader2, PlusSquare, User } from "lucide-react";
import { useEffect, useLayoutEffect, useState } from "react";
import { useRouter } from 'next/navigation'
import { Input } from "@web/components/ui/input";
import useSWR from "swr";
import { fetcher, swrFetcher } from "@web/utils/fetcher";
import { toast } from "sonner";

const formSchema = z.object({
	type: z.enum(["public", "protected", "private"]),
	password: z.string().optional(),
	users: z.array(z.coerce.number()).min(1, { message: "Please select at least one friend." })
}).superRefine((schema, ctx) => {
	const { type, password, users } = schema;
	if (type === "protected" && password?.length == 0) {
		ctx.addIssue({
			code: z.ZodIssueCode.custom,
			message: `Password must be set for Protected chat.`,
			path: ["password"],
		})
	} else if (type === "private" && users?.length > 1) {
		ctx.addIssue({
			code: z.ZodIssueCode.custom,
			message: `You can only select one friend for Private chat.`,
			path: ["users"],
		})
	}
})

export default function NewChatButton() {
	const router = useRouter()

	const [open, setOpen] = useState(false)

	const { data, error, isLoading } = useSWR(`/friend/all`, swrFetcher);

	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			type: "public",
			password: "",
			users: []
		},
	})

	const type = form.watch("type");

	useEffect(() => {
		if (open) {
			form.reset()
		}
	}, [form, open])

	useEffect(() => {
		if (type != "protected") {
			form.setValue("password", "")
		}
	}, [form, type])

	const [loading, setLoading] = useState(false)
	async function onSubmit(values: z.infer<typeof formSchema>) {
		setLoading(true)
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		console.log(values)

		const data = await fetcher(`/chat/create`, "POST", {
			type: values.type,
			password: values.password,
			users: values.users,
		});
		setLoading(false);
		if (data.status != 200 || !data.json.id) {
			form.setError("root", {
				message: data.json.error || "Failed to create chat.",
			})
			toast.error(data.json.error || "Failed to create chat.");
			return;
		} else {
			toast.success("Chat created!");
			form.reset();
			router.push(`/chat/${data.json.id}`);
		}
	}

	if (error) return <div>failed to load</div>

	return (
		<AlertDialog open={open}>
			<AlertDialogTrigger asChild>
				<Button size="sm" variant="ghost" className="hover:bg-gray-700" onClick={() => setOpen(true)}>
					<PlusSquare className="h-6 w-6" />
				</Button>
			</AlertDialogTrigger>
			<AlertDialogContent className="bg-gray-950">
				<AlertDialogHeader>
					<AlertDialogTitle>New Chat</AlertDialogTitle>
					<AlertDialogDescription>
						You can create a new chat by selecting options below.
					</AlertDialogDescription>
				</AlertDialogHeader>
				<Form {...form}>
					<form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
						<FormField
							control={form.control}
							name="type"
							render={({ field }) => (
								<FormItem>
									<FormLabel>Type</FormLabel>
									<FormControl>
										<Select onValueChange={field.onChange} defaultValue={field.value}>
											<SelectTrigger>
												<SelectValue />
											</SelectTrigger>
											<SelectContent>
												<SelectItem value="public">Public</SelectItem>
												<SelectItem value="private">Private</SelectItem>
												<SelectItem value="protected">Protected</SelectItem>
											</SelectContent>
										</Select>
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<FormField
							control={form.control}
							name="password"
							render={({ field }) => (
								<FormItem>
									<FormLabel>Password</FormLabel>
									<FormControl>
										<Input type="text" placeholder="password" {...field} disabled={type != "protected"} />
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						{isLoading ? <Loader2 className="animate-spin" /> : (
							<FormField
								control={form.control}
								name="users"
								render={({ field }) => (
									<FormItem>
										<FormLabel>Friends</FormLabel>
										<FormControl>
											{!isLoading && data && data.friends ? (
												<MultiSelect onValueChange={field.onChange}>
													{data.friends.map((friend: any) =>
														<MultiSelectItem value={friend.id} key={`${friend.id}${friend.username}`}>{friend.username}</MultiSelectItem>
													)}
												</MultiSelect>
											) : (
												<MultiSelectItem value={"none"} key={`none123`}><Loader2 className="animate-spin" /></MultiSelectItem>
											)}
										</FormControl>
										<FormMessage />
									</FormItem>
								)}
							/>
						)}
						<AlertDialogFooter>
							<AlertDialogCancel onClick={() => setOpen(false)}>Cancel</AlertDialogCancel>
							<Button type="submit" disabled={loading}>
								{loading ? <Loader2 className="animate-spin" /> : "Create"}
							</Button>
						</AlertDialogFooter>
					</form>
				</Form>
			</AlertDialogContent>
		</AlertDialog>
	)
}