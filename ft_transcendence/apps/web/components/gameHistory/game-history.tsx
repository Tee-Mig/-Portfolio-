"use client";

import { swrFetcher } from "@web/utils/fetcher";
import { Game, columns } from "./columns"
import { DataTable } from "./data-table"
import useSWR from "swr";

export default function GameHistory({ userId }: { userId: string }) {
	const { data, error, isLoading, mutate } = useSWR(`/user/${userId}/game`, swrFetcher, { refreshInterval: 1000 })

	return (
		<div className="container mx-auto overflow-scroll">
			{isLoading || error ? (
				<div>Loading...</div>
			) : (
				<DataTable columns={columns} data={data} />
			)}
		</div>
	)
}
