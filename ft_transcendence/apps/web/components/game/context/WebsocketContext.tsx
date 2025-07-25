"use client";

import { env } from "@web/env";
import { createContext, useRef } from "react";
import { io, Socket } from 'socket.io-client';

export const socket = io(env.NEXT_PUBLIC_NESTJS_SERVER, {
	withCredentials: true,
	auth: (cb) => {
		try {
			cb({ token: localStorage.getItem('token') });
		} catch (e) {
			cb({ token: '' });
		}
	},
});
export const WebsocketContext = createContext<Socket>(socket);
export const WebsocketProvider = WebsocketContext.Provider;
