'use client'
import { Button } from "@web/components/ui/button"
import Image from "next/image"

import {
	Table,
	TableBody,
	TableCell,
	TableRow,
} from "@web/components/ui/table"
import { cn } from "@web/utils/utils"
import { MessageSquare } from "lucide-react"
import { Tooltip, TooltipContent, TooltipProvider, TooltipTrigger } from "@web/components/ui/tooltip"
import Link from "next/link"
import useSWR from "swr"
import { swrFetcher } from "@web/utils/fetcher"

export default function Chats() {
	const { data, error, isLoading, mutate } = useSWR('/chat/all', swrFetcher, { refreshInterval: 1000 })
	if (isLoading) return <div className="animate-pulse">Loading...</div>
	if (error) return <div>Error</div>
	if (data.length <= 0) return <div>No chat</div>

	return (
		<div className="container mx-auto overflow-scroll">
			<Table>
				<TableBody>
					{data?.length ?
						data.map((chat: any) => {
							return (
								<TableRow key={chat.id}>
									<TableCell key={chat.id + + "cell1"}>
										<div className="flex">
											{chat.users && chat.users.map((u: any, index: number) => {
												if (index >= 3) return null
												return (
													<Image
														key={u.id + index + u.username}
														src={u.pfp}
														className={cn("w-8 h-8 rounded-full pointer-events-none", index > 0 && "-ml-2")}
														width={32}
														height={32}
														alt="avatar"
													/>
												)
											})}
											{chat.users.length > 3 && (
												<div className="w-8 h-8 rounded-full bg-gray-200 flex items-center justify-center text-gray-500 -ml-2">
													+{chat.users.length - 3}
												</div>
											)}
										</div>
									</TableCell>
									<TableCell key={chat.id + "cell2"}>
										<div className="max-w-[100px] overflow-ellipsis">
											<p className="font-bold text-foreground text-ellipsis">
												{chat.users.length && chat.users.map((u: any, index: number) => {
													if (index >= 3) return null
													return (
														<span key={u.username + index}>
															{index > 0 && ", "}
															{u.username}
															{index == 2 && chat.users.length > 3 && "..."}
														</span>
													)
												})}
											</p>
											<p className="text-muted-foreground max-w-xl overflow-hidden">{chat.messages.length === 1 ? (chat.messages[0].content as string) : "..."}</p>
										</div>
									</TableCell>
									<TableCell>
										{chat.type}
									</TableCell>
									{/* <TableCell key={chat.id + "cell3"}>
										{chat.newMessages > 0 &&
											<span
												className="ml-3 inline-block rounded-full py-0.5 px-3 text-xs font-bold bg-blue-600 text-white"
											>
												{chat.messages}
											</span>
										}
									</TableCell> */}
									<TableCell key={chat.id + "cell4"}>
										<TooltipProvider>
											<Tooltip>
												<TooltipTrigger asChild>
													<Link href={`/chat/${chat.id}/${chat.password}`}>
														<Button size="sm" variant="ghost" className="hover:bg-gray-700">
															<MessageSquare className="h-4 w-4" />
														</Button>
													</Link>
												</TooltipTrigger>
												<TooltipContent>
													<p>Open Chat</p>
												</TooltipContent>
											</Tooltip>
										</TooltipProvider>

									</TableCell>
								</TableRow>
							)
						})
						: (
							<TableRow>
								<TableCell colSpan={Object.keys(data).length} className="h-24 text-center">
									No Chats.
								</TableCell>
							</TableRow>
						)}
				</TableBody>
			</Table>
		</div>
	)
}
