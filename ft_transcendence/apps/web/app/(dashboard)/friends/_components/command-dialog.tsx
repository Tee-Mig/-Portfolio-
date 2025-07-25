"use client"

import * as React from "react"
import { Search, UserCheck } from "lucide-react"

import {
	CommandDialog,
	CommandEmpty,
	CommandGroup,
	CommandInput,
	CommandItem,
	CommandList,
	CommandSeparator,
	CommandShortcut,
} from "@web/components/ui/command"
import useSWR from "swr"
import { swrFetcher } from "@web/utils/fetcher"
import { Avatar, AvatarFallback, AvatarImage } from "@web/components/ui/avatar"
import { useRouter } from 'next/navigation'
import Link from "next/link"
import { Button } from "@web/components/ui/button"

export function CommandDialogComp() {
	const router = useRouter()
	const [open, setOpen] = React.useState(false)
	const { data, error, isLoading } = useSWR('/user/all', swrFetcher)

	React.useEffect(() => {
		const down = (e: KeyboardEvent) => {
			if (e.key === "k" && (e.metaKey || e.ctrlKey)) {
				e.preventDefault()
				setOpen((open) => !open)
			}
		}

		document.addEventListener("keydown", down)
		return () => document.removeEventListener("keydown", down)
	}, [])

	const runCommand = React.useCallback((command: () => unknown) => {
		setOpen(false)
		command()
	}, [])

	return (
		<>
			<div className="flex items-center">
				<Button variant={"ghost"} onClick={() => setOpen(true)}><Search /></Button>
				<p className="text-sm text-muted-foreground">
					Or press{" "}
					<kbd className="pointer-events-none inline-flex h-5 select-none items-center gap-1 rounded border bg-muted px-1.5 font-mono text-[10px] font-medium text-muted-foreground opacity-100">
						<span className="text-xs">⌘</span>K
					</kbd>
					{" "}to search for a user.
				</p>
			</div>
			<CommandDialog open={open} onOpenChange={setOpen}>
				<CommandInput placeholder="Type a username..." />
				<CommandList>
					<CommandEmpty>{isLoading ? "Loading..." : error ? "Error occurred" : "No users found."}</CommandEmpty>
					{!isLoading && !error && data && data && data.length > 0 && (
						<CommandGroup heading="Users">
							{data.map((user: any, idx: number) => (
								<CommandItem value={user.id} key={user.username + idx} onSelect={() => {
									runCommand(() => router.push(`/profile/${user.id}`))
								}}>

									<Avatar className="mr-2 h-4 w-4 select-none" tabIndex={-1}>
										<AvatarImage className="rounded-full" alt="User Avatar" src={user.pfp} tabIndex={-1} />
									</Avatar>
									<span>{user.username}</span>
									{user.isFriend && (
										<CommandShortcut>
											<UserCheck className="h-4 w-4 text-green-500" />
										</CommandShortcut>
									)}
								</CommandItem>
							))}
						</CommandGroup>
					)}
				</CommandList>
			</CommandDialog >
		</>
	)
}
