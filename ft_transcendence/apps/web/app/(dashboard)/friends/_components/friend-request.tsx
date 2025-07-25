"use client";

import { Card } from "@web/components/card/card";
import { Badge } from "@web/components/ui/badge";
import { Button } from "@web/components/ui/button";
import { ArrowUpRight, Check, Loader2, X } from "lucide-react";
import Image from "next/image";
import {
	Tooltip,
	TooltipContent,
	TooltipProvider,
	TooltipTrigger,
} from "@web/components/ui/tooltip"
import Link from "next/link";
import { fetcher } from "@web/utils/fetcher";
import { toast } from "sonner";
import { useState } from "react";

export function FriendRequestCard({ id, name, avatar, status }: {
	id: number,
	name: string;
	avatar: string;
	status: string;
}) {
	const [isLoading, setIsLoading] = useState(false);
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

				<div className="flex float-right">
					<TooltipProvider>
						<Tooltip>
							<TooltipTrigger asChild>
								<Button size="sm" variant="ghost" disabled={isLoading} className="hover:bg-green-500" onClick={async (e) => {
									e.preventDefault();
									setIsLoading(true);
									const res = await fetcher(`/friend/accept`, "POST", { id: id });
									if (res.status === 200 || res.status === 208) {
										setIsLoading(false);
										toast.success(res.json.msg);
										return
									} else if (res.status === 400) {
										setIsLoading(false);
										toast.error(res.json.error);
										return
									}
									setIsLoading(false);
									toast.error("An unknown error occurred");
								}}>
									{isLoading ? <Loader2 className="animate-spin" /> : <Check className="h-4 w-4" />}
								</Button>
							</TooltipTrigger>
							<TooltipContent asChild>
								<Button size="sm" variant="ghost" className="hover:bg-green-500">
									<p>Accept</p>
								</Button>
							</TooltipContent>
						</Tooltip>
					</TooltipProvider>

					<TooltipProvider>
						<Tooltip>
							<TooltipTrigger asChild>
								<Button size="sm" variant="ghost" disabled={isLoading} className="hover:bg-red-500" onClick={async (e) => {
									e.preventDefault();
									setIsLoading(true);
									const res = await fetcher(`/friend/refuse`, "POST", { id: id });
									if (res.status === 200 || res.status === 208) {
										setIsLoading(false);
										toast.success(res.json.msg);
										return
									} else if (res.status === 400) {
										setIsLoading(false);
										toast.error(res.json.error);
										return
									}
									setIsLoading(false);
									toast.error("An unknown error occurred");
								}}>
									{isLoading ? <Loader2 className="animate-spin" /> : <X className="h-4 w-4" />}
								</Button>
							</TooltipTrigger>
							<TooltipContent>
								<p>Refuse</p>
							</TooltipContent>
						</Tooltip>
					</TooltipProvider>
				</div>
			</div>
		</Card >
	)
}