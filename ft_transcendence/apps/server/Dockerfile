# development
FROM node:lts-bullseye-slim AS base

WORKDIR /usr/src/server

# prisma engine requires openssl in order to work properly (ex: pnpm dlx prisma generate)
RUN apt-get update && apt-get -y install openssl && apt-get install -y procps

COPY [ "package.json", "./" ]

FROM base AS development

RUN corepack enable pnpm && pnpm install

COPY ./prisma ./prisma

# RUN corepack enable pnpm && pnpm prisma migrate dev

RUN corepack enable pnpm && pnpm prisma generate

CMD [ "pnpm", "start:dev" ]


# Production
FROM base AS production

RUN corepack enable pnpm && pnpm install --production

COPY . .

RUN corepack enable pnpm && pnpm add global @nestjs/cli

# RUN corepack enable pnpm && pnpm prisma migrate deploy

RUN corepack enable pnpm && pnpm prisma generate

RUN corepack enable pnpm && pnpm build

CMD [ "pnpm", "start:prod" ]


## Instructions:
## ------------
#pnpm install --frozen-lockfile --production

#--production: pnpm will not install any package listed in devDependencies if the NODE_ENV environment variable is set to production. 
#              Use this flag to instruct pnpm to ignore NODE_ENV and take its production-or-not status from this flag instead.

#--frozen-lockfile: Don’t generate a pnpm.lock lockfile and fail if an update is needed.

#docker build --target dev --tag nest-dock .


#docker run --detach --publish 3000:3000 nest-dock

