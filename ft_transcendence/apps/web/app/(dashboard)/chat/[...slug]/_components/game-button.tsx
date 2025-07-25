"use client";

import {
	AlertDialog,
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
import { Button } from "@web/components/ui/button";
import { Gamepad2, Loader2 } from "lucide-react";
import { useState } from "react";
import { useRouter } from "next/navigation";
import { Label } from "@web/components/ui/label";
import { RadioGroup, RadioGroupItem } from "@web/components/ui/radio-group";

const formSchema = z.object({
	mode: z.enum(["normal", "mode1", "mode2"]),
})

export default function GameButtonDialog() {
	const router = useRouter()

	const form = useForm<z.infer<typeof formSchema>>({
		resolver: zodResolver(formSchema as any),
		defaultValues: {
			mode: "normal",
		},
	})
	const [loading, setLoading] = useState(false)
	async function onSubmit(values: z.infer<typeof formSchema>) {
		setLoading(true)
		// Do something with the form values.
		// ✅ This will be type-safe and validated.
		console.log(values)

		// sleep for 4 seconds
		router.push(`/game/create/${values.mode}`)
	}

	const [open, setOpen] = useState(false)

	return (
		<AlertDialog open={open}>
			<AlertDialogTrigger asChild>
				<Button size="sm" variant="ghost" className="hover:bg-gray-700" onClick={() => setOpen(true)}>
					<Gamepad2 className="w-6 h-6" />
				</Button>
			</AlertDialogTrigger>
			<AlertDialogContent className="bg-gray-950">
				<AlertDialogHeader>
					<AlertDialogTitle>Create New Game</AlertDialogTitle>
					<AlertDialogDescription>
						You can create a new game by selecting option below.
					</AlertDialogDescription>
				</AlertDialogHeader>
				<Form {...form}>
					<form onSubmit={form.handleSubmit(onSubmit)} className="space-y-8">
						<FormField
							control={form.control}
							name="mode"
							render={({ field }) => (
								<FormItem>
									<FormLabel>Type</FormLabel>
									<FormControl>
										<div className="flex flex-col space-y-1.5">
											<Label htmlFor="mode">Mode</Label>
											<RadioGroup onValueChange={field.onChange}
												defaultValue={field.value}>
												<div className="flex items-center space-x-2">
													<RadioGroupItem value="normal" id="r1" />
													<Label htmlFor="r1">Normal</Label>
												</div>
												<div className="flex items-center space-x-2">
													<RadioGroupItem value="mode1" id="r2" />
													<Label htmlFor="r2">Mode 1</Label>
												</div>
												<div className="flex items-center space-x-2">
													<RadioGroupItem value="mode2" id="r3" />
													<Label htmlFor="r3">Mode 2</Label>
												</div>
											</RadioGroup>
										</div>
									</FormControl>
									<FormMessage />
								</FormItem>
							)}
						/>
						<AlertDialogFooter>
							<AlertDialogCancel onClick={() => setOpen(false)}>Cancel</AlertDialogCancel>
							<Button type="submit" disabled={loading}>
								{loading ? <Loader2 className="animate-spin" /> : "Create"}
							</Button>
						</AlertDialogFooter>
					</form>
				</Form>
			</AlertDialogContent>
		</AlertDialog>
	)
}