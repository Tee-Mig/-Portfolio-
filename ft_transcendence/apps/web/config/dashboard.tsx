import { DashboardConfig } from "@web/types/types";
import { Gamepad2, LayoutDashboard, MessagesSquare, Users } from "lucide-react";

export const dashboardConfig: DashboardConfig = [
	{
		title: "Dashboard",
		href: "/dashboard",
		icon: LayoutDashboard,
	},
	{
		title: "Game",
		href: "/game",
		icon: Gamepad2,
	},
	{
		title: "Friends",
		href: "/friends",
		icon: Users,
	},
	{
		title: "Chat",
		href: "/chat",
		icon: MessagesSquare,
	},
]
