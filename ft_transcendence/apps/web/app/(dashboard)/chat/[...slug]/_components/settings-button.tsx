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
import { MultiSelect, MultiSelectItem } from "@tremor/react";
import { Button } from "@web/components/ui/button";
import { Loader2, Settings } from "lucide-react";
import { useEffect, useState } from "react";
import { Input } from "@web/components/ui/input";
import { toast } from "sonner";
import { cn } from "@web/utils/utils";
import { KeyedMutator } from "swr";
import { fetcher } from "@web/utils/fetcher";
import { useRouter } from "next/navigation";

const formSchema = z.object({
	type: z.enum(["public", "protected", "private"]),
	password: z.string().optional(),
	users: z.array(z.string()).min(1, { message: "Please select at least one friend." }),
	admins: z.array(z.string()),
	owner: z.string(),
	banned: z.array(z.string()),
})

export default function SettingsButtonAlertDialog({ chatID, data, error, isLoading, mutate }: { chatID: string, data: any, error: any, isLoading: boolean, mutate: KeyedMutator<any> }) {
	const router = useRouter()

	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			type: data.type || "public",
			password: "",
			users: (data.users as any[]).map((val) => { return `${val.id}` }) || [],
			admins: (data.admins as any[]).map((val) => { return `${val.id}` }) || [],
			owner: `${data.owner.id}` || "",
			banned: (data.banned as any[]).map((val) => { return `${val.id}` }) || [],
		},
	})
	const type = form.watch("type");
	useEffect(() => {
		if (type != "protected") {
			form.setValue("password", "")
		}
	}, [form, type])

	useEffect(() => {
		if (data) {
			form.setValue("type", data.type)
			const users = form.getValues("users") as string[];
			users.push(...(data.users as any[]).map((val: any) => { return `${val.id}` }));
			form.setValue("users", users.filter(function (item, pos) {
				return users.indexOf(item) == pos;
			}))
			const admins = form.getValues("admins") as string[];
			admins.push(...(data.admins as any[]).map((val: any) => { return `${val.id}` }));
			form.setValue("admins", admins.filter(function (item, pos) {
				return admins.indexOf(item) == pos;
			}));
			form.setValue("owner", `${data.owner.id}` || "")
			const banned = form.getValues("banned") as string[];
			banned.push(...(data.banned as any[]).map((val: any) => { return `${val.id}` }));
			form.setValue("banned", banned.filter(function (item, pos) {
				return banned.indexOf(item) == pos;
			}))
		}
	}, [])

	const [loading, setLoading] = useState(false)
	async function onSubmit(values: z.infer<typeof formSchema>) {
		setLoading(true)
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		console.log(values)
		// sleep for 4 seconds
		const data = await fetcher(`/chat/update`, "POST", {
			id: parseInt(chatID) || "",
			type: values.type,
			password: values.password,
			users: values.users,
			admins: values.admins,
			owner: values.owner,
			banned: values.banned,
		});
		setLoading(false);
		if (data.status != 200) {
			toast.error(data.json.error);
			return;
		} else {
			form.reset();
			const elem = (document.getElementById("scrollArea") as HTMLDivElement);
			elem.scrollTo(0, elem.scrollHeight);
			mutate();
			toast.success("Updated settings.");
		}
	}

	const [open, setOpen] = useState(false)

	if (error) return <div>Error</div>

	return (
		<AlertDialog open={open}>
			<AlertDialogTrigger asChild>
				<Button size="sm" variant="ghost" className="hover:bg-gray-700" onClick={() => setOpen(true)}>
					<Settings className="h-6 w-6" />
				</Button>
			</AlertDialogTrigger>
			<AlertDialogContent className="bg-gray-950">
				<AlertDialogHeader>
					<AlertDialogTitle>Update Chat</AlertDialogTitle>
					<AlertDialogDescription>
						You can update the current chat by selecting options below.
					</AlertDialogDescription>
				</AlertDialogHeader>
				<Form {...form}>
					<form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8 overflow-hidden">
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
										<Input type="text" placeholder="New password" disabled={form.getValues().type != "protected"} defaultValue={field.value} {...field} />
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<FormField
							control={form.control}
							name="users"
							render={({ field }) => (
								<FormItem>
									<FormLabel>Users</FormLabel>
									<FormControl>
										<MultiSelect onValueChange={field.onChange} defaultValue={field.value}>
											{!isLoading && data.allUsers && data.allUsers.map((friend: any) =>
												<MultiSelectItem value={`${friend.id}`} key={`${friend.id}${friend.username}users`}>{friend.username}</MultiSelectItem>
											)}
										</MultiSelect>
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<FormField
							control={form.control}
							name="admins"
							render={({ field }) => (
								<FormItem>
									<FormLabel>Admins</FormLabel>
									<FormControl>
										<MultiSelect onValueChange={field.onChange} defaultValue={field.value}>
											{!isLoading && data.users && data.users.map((friend: any) =>
												<MultiSelectItem value={`${friend.id}`} key={`${friend.id}${friend.username}admins`}>{friend.username}</MultiSelectItem>
											)}
										</MultiSelect>
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<FormField
							control={form.control}
							name="owner"
							render={({ field }) => (
								<FormItem>
									<FormLabel>Owner</FormLabel>
									<FormControl>
										<Select onValueChange={field.onChange} defaultValue={field.value}>
											<SelectTrigger>
												<SelectValue />
											</SelectTrigger>
											<SelectContent>
												{!isLoading && data.users && data.users.map((friend: any) =>
													<SelectItem value={`${friend.id}`} key={`${friend.id}${friend.username}owner`}>{friend.username}</SelectItem>
												)}
											</SelectContent>
										</Select>
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<FormField
							control={form.control}
							name="banned"
							render={({ field }) => (
								<FormItem>
									<FormLabel>Banned</FormLabel>
									<FormControl>
										<MultiSelect onValueChange={field.onChange} defaultValue={field.value}>
											{!isLoading && data.allUsers && data.allUsers.map((friend: any) =>
												<MultiSelectItem value={`${friend.id}`} key={`${friend.id}${friend.username}banned`}>{friend.username}</MultiSelectItem>
											)}
										</MultiSelect>
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<AlertDialogFooter>
							<Button type="button" disabled={loading} onClick={(e) => {
								e.preventDefault()
								mutate()
								setOpen(false)
								setTimeout(() => {
									setOpen(true)
								}, 200)
							}}>
								{loading ? <Loader2 className="animate-spin" /> : "Refresh"}
							</Button>
							<Button type="button" disabled={loading} className={cn(form.getValues().type != "public" && "hidden", "bg-green-500")} onClick={async (event) => {
								event.preventDefault()
								try {
									navigator.clipboard.writeText(window.location.href).then(() => toast.success("Copied to clipboard!"))
								} catch (err) {
									toast.error("Failed to copy to clipboard")
								}
							}}>
								{loading ? <Loader2 className="animate-spin" /> : "Share"}
							</Button>
							<Button type="button" className="bg-red-500" disabled={loading} onClick={async (e) => {
								e.preventDefault()
								const data = await fetcher(`/chat/leave`, "POST", {
									id: chatID || "",
								});
								setLoading(false);
								if (data.status != 200) {
									toast.error(data.json.error);
									return;
								} else {
									toast.success("You left the chat.");
									setOpen(false)
									router.push("/chat")
								}
							}}>
								{loading ? <Loader2 className="animate-spin" /> : "Leave"}
							</Button>
							<AlertDialogCancel onClick={() => setOpen(false)}>Cancel</AlertDialogCancel>
							<Button type="submit" disabled={loading}>
								{loading ? <Loader2 className="animate-spin" /> : "Save"}
							</Button>
						</AlertDialogFooter>
					</form>
				</Form>
			</AlertDialogContent>
		</AlertDialog>
	)
}