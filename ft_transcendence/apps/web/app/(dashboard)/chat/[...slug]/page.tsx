'use client'

import { Button } from "@web/components/ui/button";
import { AvatarImage, AvatarFallback, Avatar } from "@web/components/ui/avatar"
import { Input } from "@web/components/ui/input"
import { Gamepad2, Loader2, Settings, Swords } from "lucide-react";
import { ScrollArea } from "@web/components/ui/scroll-area"
import { cn } from "@web/utils/utils";
import SettingsButtonAlertDialog from "./_components/settings-button";
import { DropdownMenu, DropdownMenuContent, DropdownMenuItem, DropdownMenuTrigger } from "@web/components/ui/dropdown-menu";
import { Tooltip, TooltipContent, TooltipProvider, TooltipTrigger } from "@web/components/ui/tooltip";
import Link from "next/link";
import useSWR from "swr";
import { fetcher, swrFetcher } from "@web/utils/fetcher";
import React, { useEffect, useRef, useState } from "react";
import { useRouter } from 'next/navigation'
import {
	Form,
	FormControl,
	FormField,
	FormItem,
	FormLabel,
	FormMessage,
} from "@web/components/ui/form"
import { zodResolver } from "@hookform/resolvers/zod"
import { useForm } from "react-hook-form"
import * as z from "zod"
import { toast } from "sonner";
import PasswordLock from "./_components/password-page";
import GameButtonDialog from "./_components/game-button";

const formSchema = z.object({
	content: z.string(),
})

export default function Chat({ params }: { params: { slug: string[] } }) {
	const router = useRouter()

	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			content: "",
		},
	})

	const [loading, setLoading] = React.useState(false)
	async function onSubmit(values: z.infer<typeof formSchema>) {
		setLoading(true)
		// Do something with the form values.
		// ✅ This will be type-safe and validated.

		if (values.content.length < 1) {
			setLoading(false);
			return;
		}
		// sleep for 4 seconds
		const data = await fetcher(`/chat/send`, "POST", {
			id: parseInt(chatID) || "",
			content: values.content,
		});
		setLoading(false);
		if (data.status != 200) {
			form.setError("content", {
				message: data.json.error,
			})
			return;
		} else {
			toast.success("Message sent.");
			form.reset();
			const elem = (document.getElementById("scrollArea") as HTMLDivElement);
			elem.scrollTo(0, elem.scrollHeight);
			mutate();
		}
	}

	const [windowDimension, detectDim] = useState<{ winWidth: number, winHeight: number }>({
		winWidth: window.innerWidth,
		winHeight: window.innerHeight
	})
	const [heightMessageBox, setHeightMessageBox] = useState<number>(500)
	const [width, setWidth] = useState<number>(800)

	const margeMessageBox = 20
	const widthMarge = 280

	const detectSize = () => {
		detectDim({
			winWidth: window.innerWidth,
			winHeight: window.innerHeight
		})
	}
	useEffect(() => {
		window.addEventListener('resize', detectSize);
		return () => {
			window.removeEventListener('resize', detectSize);
		}
	}, [windowDimension])

	useEffect(() => {
		setHeightMessageBox(windowDimension.winHeight - 150 - margeMessageBox * 2)
		setWidth(windowDimension.winWidth - widthMarge)
	}, [windowDimension])

	const [chatID, setChatID] = useState(params.slug[0] || "")
	const [password, setPassword] = useState(params.slug[1] || "")

	const lastMessageRef = useRef(null);

	const { data, error, isLoading, mutate } = useSWR(`/chat/${chatID}/${password}`, swrFetcher, { refreshInterval: 1000 })
	useEffect(() => {
		if (error || !data || isLoading || !lastMessageRef.current) return;
		(lastMessageRef.current as any).scrollIntoView({ behavior: "smooth" });
	}, [data])
	if (chatID === "") return <div>Invalid Chat ID</div>
	if (isLoading) return <div className="animate-pulse">Loading...</div>
	if (error || !data.id) return <PasswordLock error={error} data={data} chatID={chatID} />

	return (
		<div className="flex">
			<section className="flex flex-col w-full">
				<header className="absolute top-0 p-[6px]">
					<div className="flex">
						<h2 className="text-xl font-bold flex items-center gap-2">
							{data && data.users.map((user: any, index: number) => {
								if (index >= 3) return null
								return (
									<Avatar className={cn("relative w-10 h-10 pointer-events-none", index > 0 && "-ml-4")} key={user.id + "_" + index + "topfp"}>
										<AvatarImage className="rounded-full" alt="User Avatar" src={user.pfp} />
										<AvatarFallback>U</AvatarFallback>
									</Avatar>
								)
							})}
							{data && data.users.length > 3 && (
								<div className="w-10 h-10 rounded-full bg-gray-200 flex items-center justify-center text-gray-500 -ml-4">
									+{data.users.length - 3}
								</div>
							)}
							<div>
								{data && data.users.length && data.users.map((user: any, index: number) => {
									if (index >= 3) return null
									return (
										<span key={user.username + index + "topusername"}>
											{index > 0 && ", "}
											{user.username}
											{index == 2 && data.users.length > 3 && "..."}
										</span>
									)
								})}
								<span className="text-xs text-muted-foreground block">{data ? data.type : "?"}</span>
							</div>
						</h2>
						<SettingsButtonAlertDialog chatID={chatID} data={data} error={error} isLoading={isLoading} mutate={mutate} />
					</div>
				</header>
				<div
					style={{
						display: "flex",
						flexDirection: "column",
						position: "absolute",
						width: `${width}px`,
						left: `${widthMarge}px`,
					}}
					className="lg:px-[100px] md:px-[50px] px-[10px]"
				>
					<ScrollArea style={{ height: `${heightMessageBox}px` }} className="pt-2 border-t dark:border-zinc-700 rounded h-96" id="scrollArea">
						{data && data.messages.map((message: any, index: number) =>
							message.author.isFromUser ?
								(
									<div className="flex items-end gap-2 py-2" key={`${message.id} + ${message.username}`} id={index === data.messages.length - 1 ? "lastMsg" : ""} ref={lastMessageRef}>
										<Avatar className="relative overflow-visible w-10 h-10">
											<AvatarImage alt="User Avatar" src={message.author.pfp} className="rounded-full" />
											<AvatarFallback>U</AvatarFallback>
										</Avatar>
										<div className="rounded-lg bg-blue-500 text-white p-2 mr-3 max-w-xl break-words">
											<p className="font-extrabold text-left">You</p>
											<p className="text-sm text-justify">{message.content}</p>
											{message.isInvite && (
												<div className="space-x-2 space-y-2">
													<Button onClick={() => {
														router.push(message.joinLink)
													}}>
														Join
													</Button>
													<Button onClick={() => {
														router.push(message.watchLink)
													}}>
														Watch
													</Button>
												</div>
											)}
										</div>
									</div>
								)
								: (
									<div className="flex items-end gap-2 justify-start py-2" key={message.id + message.content}>
										<DropdownMenu>
											<DropdownMenuTrigger className="hover:opacity-70" ref={lastMessageRef}>
												<Avatar className="relative overflow-visible w-10 h-10">
													<AvatarImage alt="User Avatar" src={message.author.pfp} className="rounded-full" />
													<AvatarFallback>U</AvatarFallback>
												</Avatar>
											</DropdownMenuTrigger>
											<DropdownMenuContent align="end">
												<Link href={`/profile/${message.author.id}`}>
													<DropdownMenuItem>
														View Profile
													</DropdownMenuItem>
												</Link>
												<DropdownMenuItem onClick={async (e) => {
													e.preventDefault();
													const data = await fetcher(`/user/block`, "POST", {
														id: message.author.id,
													});
													if (data.status != 200) {
														toast.error(data.json.error);
														return;
													} else if (data.json.msg) {
														toast.success(data.json.msg);
														return;
													}
													toast.error("An unknown error occurred");
												}}>
													Block
												</DropdownMenuItem>
												<DropdownMenuItem onClick={async (e) => {
													e.preventDefault();
													const data = await fetcher(`/chat/mute`, "POST", {
														id: chatID || "",
														userId: message.author.id,
													});
													if (data.status != 200) {
														toast.error(data.json.error);
														return;
													} else {
														toast.success("User Muted.");
													}
												}}>
													Mute 10min
												</DropdownMenuItem>
												<DropdownMenuItem onClick={async (e) => {
													e.preventDefault();
													const data = await fetcher(`/chat/kick`, "POST", {
														id: chatID || "",
														userId: message.author.id,
													});
													if (data.status != 200) {
														toast.error(data.json.error);
														return;
													} else {
														toast.success("User kicked.");
													}
												}}>
													Kick
												</DropdownMenuItem>
												<DropdownMenuItem onClick={async (e) => {
													e.preventDefault();
													const data = await fetcher(`/chat/ban`, "POST", {
														id: chatID || "",
														userId: message.author.id,
													});
													if (data.status != 200) {
														toast.error(data.json.error);
														return;
													} else {
														toast.success("User banned.");
													}
												}}>
													Ban
												</DropdownMenuItem>
											</DropdownMenuContent>
										</DropdownMenu>
										<div className="rounded-lg bg-zinc-200 dark:bg-zinc-700 p-2 mr-3 max-w-xl break-words">
											<p className="font-extrabold text-left">{message.author.username}</p>
											<p className="text-sm text-justify">{message.content}</p>
											{message.isInvite && (
												<div className="space-x-2 space-y-2">
													<Button onClick={() => {
														router.push(message.joinLink)
													}}>
														Join
													</Button>
													<Button onClick={() => {
														router.push(message.watchLink)
													}}>
														Watch
													</Button>
												</div>
											)}
										</div>
									</div>
								)
						)}
					</ScrollArea>
					<div className="bottom-0 p-4 border-t dark:border-zinc-700 w-full">
						<Form {...form}>
							<form onSubmit={form.handleSubmit(onSubmit)} className="flex items-center gap-2">
								<TooltipProvider>
									<Tooltip>
										<TooltipTrigger asChild>
											<Button size="sm" variant="ghost" className="hover:bg-gray-700">
												<GameButtonDialog />
											</Button>
										</TooltipTrigger>
										<TooltipContent>
											<p>Start Game</p>
										</TooltipContent>
									</Tooltip>
								</TooltipProvider>
								<FormField
									control={form.control}
									name="content"
									render={({ field }) => (
										<FormItem className="w-full">
											<FormControl>
												<Input className="flex-1" type="text" placeholder="Type a message..." {...field} />
											</FormControl>
											<FormMessage />
										</FormItem>
									)}
								/>
								<Button type="submit" disabled={loading || form.getValues().content == "" || (data && data.muted)}>
									{loading ? <Loader2 className="animate-spin" /> : (data && data.muted ? "Muted" : "Send")}
								</Button>
							</form>
						</Form>
					</div>
				</div>
			</section>
		</div>
	);
}
