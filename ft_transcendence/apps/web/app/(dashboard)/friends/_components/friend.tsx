"use client";

import { Card } from "@web/components/card/card";
import { Badge } from "@web/components/ui/badge";
import { Button } from "@web/components/ui/button";
import { ArrowUpRight, Eye, MessageSquare, MoreHorizontal, Router, Swords } from "lucide-react";
import Image from "next/image";
import {
	Tooltip,
	TooltipContent,
	TooltipProvider,
	TooltipTrigger,
} from "@web/components/ui/tooltip"
import {
	DropdownMenu,
	DropdownMenuContent,
	DropdownMenuItem,
	DropdownMenuTrigger,
} from "@web/components/ui/dropdown-menu"
import Link from "next/link";
import { toast } from "sonner";
import { fetcher } from "@web/utils/fetcher";
import { useRouter } from "next/navigation";

export function FriendCard({ id, name, avatar, status, isBlocked }: {
	id: number,
	name: string;
	avatar: string;
	status: string;
	isBlocked: boolean;
}) {
	const router = useRouter();
	return (
		<Card>
			<div className="p-6 flex items-center w-full justify-between hover:bg-gray-800">
				<Link className="flex" href={`/profile/${id}`}>
					<div>
						<Image
							src={avatar}
							width={48}
							height={48}
							className="rounded-full w-12 h-12"
							alt="avatar"
							loading="eager"
						/>
					</div>
					<div className="ml-4">
						<div className="items-center">
							<p className="flex">
								{name}
								<ArrowUpRight width={12} height={12} />
							</p>
							<Badge variant={`${status != "offline" ? "default" : "destructive"}`}>
								{status}
							</Badge>
						</div>
					</div>
				</Link>
				<TooltipProvider>
					<Tooltip>
						<TooltipTrigger asChild>
							<Button size="sm" variant="ghost" className="hover:bg-gray-700 space-x-2" onClick={() => {
								router.push(`/game/watch/${id}`)
							}}>
								<p>Watch game</p>
								<Eye className="h-4 w-4" />
							</Button>
						</TooltipTrigger>
						<TooltipContent>
							<p>Watch Game</p>
						</TooltipContent>
					</Tooltip>
				</TooltipProvider>
				<div className="flex float-right">
					<TooltipProvider>
						<Tooltip>
							<TooltipTrigger asChild>
								<Button size="sm" variant="ghost" className="hover:bg-gray-700" onClick={async (e) => {
									e.preventDefault();
									const data = await fetcher(`/chat/dm`, "POST", {
										id: id,
									});
									if (data.status != 200 || !data.json.url) {
										toast.error(data.json.error);
										return;
									} else {
										toast.success("Opening Chat...");
										router.push(data.json.url)
									}
								}}>
									<MessageSquare className="h-4 w-4" />
								</Button>
							</TooltipTrigger>
							<TooltipContent>
								<p>Open Chat</p>
							</TooltipContent>
						</Tooltip>
					</TooltipProvider>
					<DropdownMenu>
						<DropdownMenuTrigger asChild>
							<Button variant="ghost" size="sm" className="hover:bg-gray-700 h-9 w-10">
								<MoreHorizontal className="h-4 w-4" />
								<span className="sr-only">More</span>
							</Button>
						</DropdownMenuTrigger>
						<DropdownMenuContent align="end">
							<DropdownMenuItem onClick={async (e) => {
								e.preventDefault();
								const data = await fetcher(`/user/block`, "POST", {
									id: id,
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
								{isBlocked ? "Unblock" : "Block"} friend
							</DropdownMenuItem>
							<DropdownMenuItem onClick={async (e) => {
								e.preventDefault();
								const res = await fetcher(`/friend/remove`, "POST", { id: id });
								if (res.status === 200 || res.status === 208) {
									toast.success(res.json.msg);
									return
								} else if (res.status === 400) {
									toast.error(res.json.error);
									return
								}
								toast.error("An unknown error occurred");
							}}>
								Remove friend
							</DropdownMenuItem>
						</DropdownMenuContent>
					</DropdownMenu>
				</div>
			</div>
		</Card>
	)
}