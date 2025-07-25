import { cn } from "@web/utils/utils"

export function Card({ children, className }: {
	children: React.ReactNode
	className?: string
}) {
	return (
		<section className={cn("my-8 max-w-5xl", className)}>
			<div className="bg-gray-800/50 rounded-md shadow overflow-hidden border-[1px] border-gray-700">
				{children}
			</div>
		</section>
	)
}