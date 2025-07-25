"use client";

import { fetcher, swrFetcher } from "@web/utils/fetcher"
import useSWR from "swr"
import { SearchSelect, SearchSelectItem } from "@tremor/react";
import { Avatar, AvatarImage } from "@web/components/ui/avatar";
import { useState } from "react";
import { cn } from "@web/utils/utils";
import Image from "next/image";
import { zodResolver } from "@hookform/resolvers/zod"
import { useForm } from "react-hook-form"
import { z } from "zod"
import { Button } from "@web/components/ui/button"
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
import { toast } from "sonner";
import { Loader2 } from "lucide-react";

const formSchema = z.object({
	chatID: z.string()
})

export default function Chats({ inviteCode }: { inviteCode: string }) {
	const [chatID, setChatID] = useState<string>("");
	const [loading, setLoading] = useState<boolean>(false);

	// 1. Define your form.
	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			chatID: "",
		},
	})

	// 2. Define a submit handler.
	async function onSubmit(values: z.infer<typeof formSchema>) {
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		const data = await fetcher(`/chat/game/invite`, "POST", {
			chatID: values.chatID,
			inviteCode: inviteCode
		});
		setLoading(false);
		if (data.status != 200) {
			form.setError("chatID", {
				message: data.json.error || "Failed to send invite.",
			})
			toast.error(data.json.error || "Failed to send invite.");
			return;
		} else {
			toast.success("Invite sent!");
			form.reset();
		}
	}

	const { data, error, isLoading, mutate } = useSWR('/chat/all', swrFetcher, { refreshInterval: 1000 })
	if (isLoading) return <div className="animate-pulse">Loading...</div>
	if (error) return <div>Error</div>
	if (data.length <= 0) return <div>No chat</div>

	return (
		<Form {...form}>
			<form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
				<FormField
					control={form.control}
					name="chatID"
					render={({ field }) => (
						<FormItem className="flex justify-center">
							<FormControl>
								<SearchSelect className="max-w-xl" placeholder="Search chat..." {...field} enableClear={false}>
									{data.map((chat: any, idx: number) => (
										<SearchSelectItem key={idx + "_" + chat.id} value={`${chat.id}`}>
											<div className="flex justify-center overflow-hidden text-ellipsis">
												{chat.users && chat.users.map((u: any, index: number) => {
													if (index >= 3) return null
													return (
														<Image
															key={u.id + index}
															src={u.pfp}
															className={cn("w-4 h-4 rounded-full pointer-events-none", index > 0 && "-ml-2")}
															width={16}
															height={16}
															alt="avatar"
														/>
													)
												})}
												{chat.users.length > 3 && (
													<div className="w-8 h-8 rounded-full bg-gray-200 flex items-center justify-center text-gray-500 -ml-2">
														+{chat.users.length - 3}
													</div>
												)}
												<p className="font-bold text-foreground text-ellipsis">
													{chat.users.length && chat.users.map((u: any, index: number) => {
														if (index >= 3) return null
														return (
															<span key={u.updatedAt + "_" + index}>
																{index > 0 && ", "}
																{u.username}
																{index == 2 && chat.users.length > 3 && "..."}
															</span>
														)
													})}
												</p>
											</div>
										</SearchSelectItem>
									))}
								</SearchSelect>
							</FormControl>
							<FormMessage />
						</FormItem>
					)}
				/>
				{isLoading ? <Loader2 className="animate-spin" /> : (
					<Button type="submit">Send invite</Button>
				)}
			</form>
		</Form>
	)
}