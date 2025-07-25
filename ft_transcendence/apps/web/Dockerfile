FROM node:lts-bullseye-slim AS deps

WORKDIR /usr/src/app

COPY [ "package.json", "pnpm-lock*", "./" ]

RUN apt-get update && apt-get install build-essential -y && apt-get install python3 -y
RUN corepack enable pnpm && pnpm install --frozen-lockfile

#####
FROM deps AS development

EXPOSE 3000
WORKDIR /usr/src/app

ENV PORT=3000
ENV HOST=0.0.0.0
ENV NODE_ENV=development

COPY --from=deps /usr/src/app/node_modules ./node_modules
COPY . .

CMD ["pnpm", "dev"]

#####
FROM deps AS builder

WORKDIR /usr/src/app

ENV NODE_ENV=production
ENV NEXT_TELEMETRY_DISABLED=1

COPY --from=deps /usr/src/app/node_modules ./node_modules
COPY . .
RUN pnpm build

#####
FROM deps AS production

WORKDIR /usr/src/app

EXPOSE 3000
ENV PORT=3000
ENV HOST=0.0.0.0

ENV NODE_ENV=production

COPY --from=builder /usr/src/app/next.config.js ./
COPY --from=builder /usr/src/app/public ./
COPY --from=builder /usr/src/app/.next ./.next

CMD ["pnpm", "run", "start"]
