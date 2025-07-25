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
import { zodResolver } from "@hookform/resolvers/zod"
import { useForm } from "react-hook-form"
import * as z from "zod"
import { Icon, MultiSelect, MultiSelectItem } from "@tremor/react";
import { Button } from "@web/components/ui/button";
import { Loader2, PlusSquare, User } from "lucide-react";
import { Dispatch, SetStateAction, useEffect, useState } from "react";
import { useRouter } from 'next/navigation'
import { Input } from "@web/components/ui/input";
import { toast } from "sonner";
import { fetcher } from "@web/utils/fetcher";

const formSchema = z.object({
	otp: z.string({
		description: "Please enter a valid OTP.",
	}).min(1, { message: "Please enter a valid OTP." }),

})

export default function OTPAlert({ open, setOpen, email }: { open: boolean, setOpen: Dispatch<SetStateAction<boolean>>, email: string }) {
	const router = useRouter()

	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			otp: "",
		},
	})

	const [loading, setLoading] = useState(false)
	function onSubmit(values: z.infer<typeof formSchema>) {
		setLoading(true)
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		console.log(values)

		fetcher(`/auth/otp`, "POST", {
			otp: values.otp,
			email: email,
			step: "login"
		}).then((res) => {
			if (res.status === 200 && res.json.success && res.json.token) {
				toast.success("Logged in successfully.")
				localStorage.setItem("token", res.json.token)
				router.push("/dashboard")
				return;
			} else if (res.status === 400) {
				toast.error("Invalid OTP Code")
				form.setError("otp", {
					message: "Invalid OTP.",
				});
				setLoading(false)
				return;
			} else {
				toast.error("Something went wrong while validating OTP.")
				setLoading(false)
				return;
			}
		})
	}

	return (
		<AlertDialog open={open}>
			<AlertDialogContent className="bg-gray-950">
				<AlertDialogHeader>
					<AlertDialogTitle>OTP Verification</AlertDialogTitle>
					<AlertDialogDescription>
						You{"'"}ve enabled OTP verification for your account. Please enter the OTP sent to <b>{email}</b>.
					</AlertDialogDescription>
				</AlertDialogHeader>
				<Form {...form}>
					<form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
						<FormField
							control={form.control}
							name="otp"
							render={({ field }) => (
								<FormItem>
									<FormLabel>OTP Code</FormLabel>
									<FormControl>
										<Input type="text" placeholder="otp" {...field} />
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<AlertDialogFooter>
							<AlertDialogCancel onClick={() => {
								router.replace("/", { query: {} });
								setTimeout(() => {
									setOpen(false);
								}, 100);
							}}>Cancel</AlertDialogCancel>
							<Button type="submit" disabled={loading}>
								{loading ? <Loader2 className="animate-spin" /> : "Submit"}
							</Button>
						</AlertDialogFooter>
					</form>
				</Form>
			</AlertDialogContent>
		</AlertDialog >
	)
}