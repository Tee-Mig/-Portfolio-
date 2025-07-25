/** @type {import('next').NextConfig} */
const nextConfig = {
	// output: 'export',
	compiler: {
		removeConsole: true,
	},
	reactStrictMode: true,
	images: {
		unoptimized: true,
		domains: ['images.unsplash.com', 'media4.giphy.com', 'media3.giphy.com'],
	},
	async rewrites() {
		return [
			{
				source: '/api/:path*',
				destination: process.env.NEXT_PUBLIC_NESTJS_SERVER + '/:path*',
			},
		]
	},
}

module.exports = nextConfig
