"use client";

import { Card } from "@web/components/card/card";
import { env } from "@web/env";
import { User } from "@web/types/types";
import Image from "next/image";
import { toast } from "sonner";
import { KeyedMutator } from "swr";

export function PFPCard({ user, mutate }: { user: User; mutate: KeyedMutator<any> }) {
	return (
		<Card className="my-0">
			<div className="p-6">
				<div className="flex float-right">
					<button onClick={(e) => {
						e.preventDefault();
						document.getElementById("pfp")?.click();
					}}>
						<Image
							src={user.pfp}
							width={80}
							height={80}
							className="rounded-full hover:opacity-90 h-20 w-20"
							alt="avatar"
							loading="eager"
						/>
					</button>
					<input type="file" id="pfp" accept="image/png,image/jpeg" className="hidden" onChange={async (e) => {
						try {
							e.preventDefault();
							if (!e.target.files || !e.target.files[0]) {
								toast.error("No file selected");
								return;
							};
							if (e.target.files[0].size > 1024 * 1024 * 5) {
								toast.error("File too large, max 5MB");
								return;
							}
							toast.info("Uploading image...");
							const formdata = new FormData();
							formdata.append("file", e.target.files[0]);
							e.target.files = null;
							const res = await fetch(env.NEXT_PUBLIC_NESTJS_SERVER + "/user/pfp", {
								method: "POST",
								headers: {
									Authorization: "Bearer " + localStorage.getItem("token") || "",
								},
								body: formdata,
							});
							if (!res.ok) {
								toast.error("Failed to upload image.");
								return;
							} else {
								toast.success("Successfully uploaded image.");
								mutate();
							}
						} catch (e) {
							toast.error("Failed to upload image.");
						}
					}} />
				</div>
				<h4 className="text-2xl font-semibold text-white">Avatar</h4>
				<p className="my-3 dark:text-gray-300">
					This is your avatar.
					<br />
					Click on the avatar to upload a custom one from your files.
				</p>
			</div>
		</Card>
	)
}