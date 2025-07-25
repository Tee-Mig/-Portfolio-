'use client'
import { Button } from "@web/components/ui/button";
import { UsernameCard } from "./_components/username-card";
import { Card } from "@web/components/card/card";
import { FACard } from "./_components/2FA-card";
import Link from "next/link";
import { PFPCard } from "./_components/pfp-card";
import { swrFetcher } from "@web/utils/fetcher";
import useSWR from "swr";
import { User } from "@web/types/types";

export default function Home() {
	const { data: user, error, isLoading, mutate } = useSWR('/user/me', swrFetcher)
	if (isLoading) return <div className="animate-pulse">Loading...</div>
	if (error || !user.id) return <div>Error</div>

	return (
		<>
			<PFPCard user={user as User} mutate={mutate} />
			<UsernameCard user={user as User} mutate={mutate} />
			<FACard user={user as User} mutate={mutate} />

			<Card className="my-0">
				<div className="p-6">
					<h4 className="text-2xl font-semibold text-white">Preview</h4>
					<p className="my-3 dark:text-gray-300">
						Click below to view your public profile.
					</p>
				</div>
				<footer className="min-h-[57px] border-t-[1px] border-gray-700 py-3 px-6">
					<div className="flex items-center">
						<div className="m-auto mr-0">
							<Link href={`/profile/${user.id}`}>
								<Button size="sm" className="h-8 font-medium" type="submit">
									Preview
								</Button>
							</Link>
						</div>
					</div>
				</footer>
			</Card>
		</>
	);
}
