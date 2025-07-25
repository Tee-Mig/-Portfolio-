"use client";

import { motion } from "framer-motion";
import { Gradient } from "../../components/gradient/gradient";
import { useEffect, useState } from "react";
import { Si42 } from "react-icons/si";
import { Button } from "@web/components/ui/button";
import Link from "next/link";
import { env } from "@web/env";
import { useSearchParams } from 'next/navigation'
import { toast } from "sonner";
import { fetcher } from "@web/utils/fetcher";
import OTPAlert from "./_components/alert";
import { useRouter } from 'next/navigation'

export default function Home() {
	const searchParams = useSearchParams()
	const router = useRouter()

	const [open, setOpen] = useState(false);
	const [email, setEmail] = useState("");

	useEffect(() => {
		const gradient = new Gradient();
		gradient.initGradient("#gradient-canvas");
	}, []);

	useEffect(() => {
		if (localStorage.getItem("token") && !exec) {
			router.replace("/dashboard")
		}
	});

	const [exec, setExec] = useState(false);
	useEffect(() => {
		if (exec) return;
		const code = searchParams.get("code")
		if (!code) {
			return;
		}
		setExec(true);
		fetcher(`/auth/login?code=${code}`, "GET").then((res) => {
			if (res.status != 200) {
				toast.error(res.json.error || "Something went wrong while logging in.")
				router.replace("/", { query: {} })
				return;
			}
			if (res.json.success) {
				if (res.json.otp) {
					toast.info("Please enter the OTP sent to your email.")
					setEmail(res.json.email);
					setOpen(true);
					return;
				}
				toast.success("Logged in successfully.")
				localStorage.setItem("token", res.json.token)
				console.log(res.json)
				if (!res.json.onboarded) {
					window.location.href = "/profile";
				} else {
					window.location.href = "/dashboard";
				}
			}
		})
	})

	return (
		<div className="min-h-[100vh] sm:min-h-screen w-screen flex flex-col relative bg-gray-950 font-inter overflow-hidden">
			<svg
				style={{ filter: "contrast(125%) brightness(90%)" }}
				className="fixed z-[1] w-full h-full opacity-[35%]"
			>
				<filter id="noise">
					<feTurbulence
						type="fractalNoise"
						baseFrequency=".7"
						numOctaves="3"
						stitchTiles="stitch"
					></feTurbulence>
					<feColorMatrix type="saturate" values="0"></feColorMatrix>
				</filter>
				<rect width="100%" height="100%" filter="url(#noise)"></rect>
			</svg>
			<main className="flex flex-col justify-center h-[90%] fixed w-screen overflow-hidden z-[10] pt-[30px] pb-[320px] px-4 md:px-20 md:py-0">
				<OTPAlert open={open} setOpen={setOpen} email={email} />
				<div
					className="w-full"
				>
					<h2 className="mt-10 text-2xl font-bold leading-9 tracking-tight">
						Sign in to your account
					</h2>
					<Link href={env.NEXT_PUBLIC_NESTJS_SERVER + "/auth/login"} prefetch={false}>
						<Button className="max-w-[32rem] w-full">
							<Si42 className="w-4 h-4" />
						</Button>
					</Link>
				</div>
			</main>
			<div
				className="fixed top-0 right-0 w-[80%] md:w-1/2 h-screen bg-[#09263F]/20 max-md:hidden"
				style={{
					clipPath:
						"polygon(100px 0,100% 0,calc(100% + 225px) 100%, 480px 100%)",
				}}
			></div>
			<canvas
				style={{
					clipPath:
						"polygon(100px 0,100% 0,calc(100% + 225px) 100%, 480px 100%)",
				}}
				id="gradient-canvas"
				data-transition-in
				className="z-50 fixed top-0 right-[-2px] w-[80%] md:w-1/2 h-screen bg-gray-950 max-md:hidden"
			></canvas>
		</div>
	);
}
