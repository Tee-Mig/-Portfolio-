export default async function RootLayout({
	children,
}: {
	children: React.ReactNode;
}) {
	return (
		<div className="scroll-smooth antialiased">
			{children}
		</div>
	);
}