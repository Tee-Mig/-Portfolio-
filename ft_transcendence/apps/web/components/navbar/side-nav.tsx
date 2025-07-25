"use client";

import { dashboardConfig } from "@web/config/dashboard"
import { cn } from "@web/utils/utils"
import Image from 'next/image';
import Link from "next/link";
import { usePathname } from "next/navigation"
import { LogOut } from "lucide-react";
import { Button } from "../ui/button";
import { useContext, useEffect, useState } from "react";
import useSWR from "swr";
import { swrFetcher } from "@web/utils/fetcher";
import { Avatar, AvatarFallback, AvatarImage } from "../ui/avatar";
import { env } from "@web/env";
import { createContext } from "react";
import { io, Socket } from 'socket.io-client';

type PublicUser = {
	id: number;
	id42: number;
	email: string;
	username: string;
	pfp: string;
	status: string;
	tfaEnabled: boolean;
	tfaVerified: boolean;
	tfaOTP: string | null;
	inGame: boolean;
	createdAt: Date;
	updatedAt: Date;
};

export const socket = io(env.NEXT_PUBLIC_NESTJS_SERVER, {
	path: '/socket',
	withCredentials: true,
	auth: (cb) => {
		try {
			cb({ token: localStorage.getItem('token') });
		} catch (e) {
			cb({ token: '' });
		}
	},
});
export const WebsocketContext = createContext<Socket>(socket);
export const WebsocketProvider = WebsocketContext.Provider;

export function DashboardNav() {
	const path = usePathname()
	const socket = useContext(WebsocketContext);

	const { data: user, error, isLoading } = useSWR('/user/me', swrFetcher, { refreshInterval: 500 })

	useEffect(() => {
		const token = localStorage.getItem("token");
		if (!token) {
			window.location.href = '/'
		}
	})

	useEffect(() => {
		socket.on('user', (user: PublicUser) => {
			console.log('connected to status socket');
			localStorage.setItem('id', user.id.toString());
		});
	})

	useEffect(() => {
		socket.emit('path', {
			path: path
		});
	});

	if (!dashboardConfig?.length) {
		return null
	}
	return (
		<div className="flex h-screen w-64">
			<div className="flex w-64 flex-col">
				<div className="flex min-h-0 flex-1 flex-col border-r border-gray-700 fixed h-screen w-64">
					<div className="flex flex-1 flex-col overflow-y-auto pt-4 pb-4">
						<div className=" h-14">
							<Link href={`/dashboard`}>
								<div className="flex px-4">
									<Image
										src={"/logo/logo.png"}
										width={32}
										height={32}
										className="h-8 w-auto"
										alt="Pungy Logo"
									/>
									<h1 className="text-center text-4xl tracking-wide font-semibold">
										Pungy
									</h1>
								</div>
							</Link>
						</div>

						<nav className="mt-5 flex-1" aria-label="Sidebar">
							<div className="space-y-1 px-2">
								{dashboardConfig.map((item, index) => {
									return item.href && (
										<Link
											key={item.href + " " + index}
											href={item.href}
											className={cn(
												path.includes(item.href)
													? 'text-white'
													: 'text-gray-200',
												'group flex items-center px-2 py-2 text-sm font-medium rounded-md hover:bg-gray-700'
											)}
										>
											<item.icon
												className={cn(
													path.includes(item.href) ? 'text-white' : 'text-gray-400 group-hover:text-gray-100',
													'mr-3 h-6 w-6'
												)}
												aria-hidden="true"
											/>
											<span className={cn(
												"flex-1",
												path.includes(item.href) ? 'text-white font-bold' : 'text-gray-400 group-hover:text-gray-100'
											)}>{item.title}</span>
											{!isLoading && user && user.notifications && ((user.notifications.friendRequests > 0 && item.href.includes("/friends")) || (user.notifications.chats > 0 && item.href.includes("/chat"))) ? (
												<span
													className="ml-3 inline-block rounded-full py-0.5 px-3 text-xs font-bold bg-blue-600 text-white"
												>
													{
														item.href.includes("/friends") ? user.notifications.friendRequests : item.href.includes("/chat") ? user.notifications.chats : null
													}
												</span>
											) : null}
										</Link>
									)
								})}
							</div>
						</nav>
					</div>
					<div className="flex flex-shrink-0 border-t border-gray-700 p-4">
						<div className="block w-full flex-shrink-0">
							<div className="flex items-center justify-between">
								<div className="group flex">
									<div>
										<Avatar className="mr-2 h-10 w-10 select-none" tabIndex={-1}>
											<AvatarImage className="rounded-full" alt="User Avatar" src={user?.pfp} tabIndex={-1} />
											<AvatarFallback>U</AvatarFallback>
										</Avatar>
									</div>
									<div className="ml-3 flex">
										<Link href={`/profile`}>
											<p className="text-sm font-medium">{isLoading || error ? "loading..." : user?.username}</p>
											<p className="text-xs font-medium dark:text-slate-400 dark:group-hover:text-gray-100 group-hover:text-gray-700">Edit profile</p>
										</Link>
									</div>
								</div>
								<div className="ml-2 flex shrink-0">
									<Button
										variant="ghost"
										type="button"
										className="font-medium rounded p-1 text-white hover:text-red-500 bg-transparent hover:bg-transparent"
										onClick={() => {
											localStorage.removeItem("token");
											window.location.href = "/"
										}}
									>
										<LogOut className="h-6 w-6 flex-shrink-0" aria-hidden="true" />
									</Button>
								</div>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	)
}
