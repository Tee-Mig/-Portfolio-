"use client"

import { ColumnDef } from "@tanstack/react-table"

// This type is used to define the shape of our data.
// You can use a Zod schema here if you want.
export type Game = {
	id: string
	date: string
	status: "Won" | "Lost" | "Draw"
	opponent: string
	mode: string
}

export const columns: ColumnDef<Game>[] = [
	{
		accessorKey: "date",
		header: "Date",
	},
	{
		accessorKey: "status",
		header: "Status",
	},
	{
		accessorKey: "opponent",
		header: "Opponent",
	},
	{
		accessorKey: "mode",
		header: "Mode",
	},
]
