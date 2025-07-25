"use client";

import { Card } from "@web/components/card/card";
import GameHistory from "@web/components/gameHistory/game-history";
import { useEffect, useState } from "react";

export default function Home() {
	const [userId, setUserId] = useState("")

	useEffect(() => {
		if (typeof window !== "undefined") {
			const id = localStorage.getItem("id") || "";
			setUserId(id)
		}
	}, [])

	return (
		<div>
			<Card>
				<div className="p-6">
					<h4 className="text-2xl font-semibold text-white">Your History</h4>
					<p className="my-3 dark:text-gray-300">
						History of games played
					</p>
					<div className="max-h-96 overflow-scroll">
						{userId != "" && <GameHistory userId={userId} />}
					</div>
				</div>
			</Card>
		</div>
	);
}
