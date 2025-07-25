"use client";

import { Separator } from "@web/components/ui/separator";
import { FriendCard } from "./_components/friend";
import { FriendRequestCard } from "./_components/friend-request";
import useSWR from "swr";
import { swrFetcher } from "@web/utils/fetcher";
import { CommandDialogComp } from "./_components/command-dialog";

export default function Home() {
	const { data, error, isLoading, mutate } = useSWR('/friend/all', swrFetcher, { refreshInterval: 1000 })
	if (isLoading) return <div className="animate-pulse">Loading...</div>
	if (error || !data) return <div>Error</div>

	return (
		<div className="-mt-4">
			{data.pending && data.pending.length > 0
				&& (
					<div>
						<h4 className="text-xl font-bold flex items-center">
							Friend Requests
							<span
								className="ml-3 inline-block rounded-full py-0.5 px-3 text-xs font-bold bg-blue-600 text-white"
							>
								{data.pending.length}
							</span>
						</h4>
						{data.pending.map((friend: any, idx: number) => (
							<FriendRequestCard key={friend.name + "_" + idx} id={friend.id} name={friend.username} status={friend.status} avatar={friend.pfp} />
						))}
						<Separator className="my-8 max-w-5xl bg-white" />
					</div>
				)
			}
			<div>
				<h4 className="text-xl font-bold">
					Friends
					<CommandDialogComp />
				</h4>
				{data.friends && data.friends.length > 0
					? data.friends.map((friend: any, idx: number) => (
						<FriendCard key={friend.name + "_" + idx} id={friend.id} name={friend.username} status={friend.status} avatar={friend.pfp} isBlocked={false} />
					))
					: <div className="flex text-center justify-center">
						<p>No friends</p>
					</div>}
			</div>

			{data && data.blocked && data.blocked.length > 0 && (
				<div>
					<h4 className="text-xl font-bold">
						Blocked
					</h4>
					{data.blocked && data.blocked.length > 0
						? data.blocked.map((friend: any, idx: number) => (
							<FriendCard key={friend.name + "_" + idx} id={friend.id} name={friend.username} status={friend.status} avatar={friend.pfp} isBlocked={true} />
						))
						: <div className="flex text-center justify-center">
							<p>0 blocked user</p>
						</div>}
				</div>
			)}

		</div>
	);
}
