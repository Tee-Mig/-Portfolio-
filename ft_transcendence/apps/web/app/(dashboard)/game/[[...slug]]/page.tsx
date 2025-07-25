"use client";

import { Game } from "@web/components/game/Game";

export default function Home({ params }: { params: { slug: string[] } }) {
	return (
		<>
			<Game params={params} />
		</>
	);
}
