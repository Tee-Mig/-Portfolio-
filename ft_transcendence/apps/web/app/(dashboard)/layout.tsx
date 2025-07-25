import { DashboardNav } from "@web/components/navbar/side-nav";
import { TopNav } from "@web/components/navbar/top-nav";

export default async function RootLayout({
	children,
}: {
	children: React.ReactNode;
}) {
	return (
		<div className="scroll-smooth antialiased">
			<div className="min-h-[100vh] sm:min-h-screen w-screen flex flex-col relative bg-gray-950 font-inter overflow-hidden">
				<div className="flex z-[1]">
					<DashboardNav />
					<div className="w-screen">
						<TopNav />
						<div className="mx-auto max-w-7xl sm:px-6 lg:px-8 py-8">
							<main className="px-4 py-5 sm:p-6">
								{children}
							</main>
						</div>
					</div>
				</div>
				{/* Noise */}
				<svg
					style={{ filter: "contrast(125%) brightness(70%)" }}
					className="fixed w-full h-full opacity-[35%] cursor-not-allowed"
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
			</div>
		</div>
	);
}