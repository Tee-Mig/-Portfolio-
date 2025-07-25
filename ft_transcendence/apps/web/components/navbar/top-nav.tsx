"use client";

import Link from "next/link";
import Image from 'next/image';
import { usePathname } from "next/navigation"
import { dashboardConfig } from "@web/config/dashboard"

export function TopNav() {
	const path = usePathname()

	return (
		<div className="w-full flex items-center justify-between border-b border-gray-700 px-4 text-4xl font-semibold h-14">
			<h1 className="text-center text-2xl tracking-wide font-semibold">
				{dashboardConfig.find(item => item.href?.includes(path))?.title}
			</h1>
		</div>
	)
}