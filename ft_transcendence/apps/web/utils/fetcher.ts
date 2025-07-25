import { env } from "@web/env";

export async function fetcher(
  url: string,
  method: string = "POST",
  body?: any
): Promise<{
  json: any;
  status: number;
}> {
  try {
    var res: Response;
    if (!body) {
      res = await fetch(env.NEXT_PUBLIC_NESTJS_SERVER + url, {
        method,
        headers: {
          Authorization: "Bearer " + localStorage.getItem("token") || "",
        },
      });
    } else {
      res = await fetch(env.NEXT_PUBLIC_NESTJS_SERVER + url, {
        method,
        headers: {
          "Content-Type": "application/json",
          Authorization: "Bearer " + localStorage.getItem("token") || "",
        },
        body: JSON.stringify(body),
      });
    }

    const json = await res.json();
    return {
      json: json,
      status: res.status,
    };
  } catch (error) {
    console.error(error);
    return {
      json: error,
      status: 500,
    };
  }
}

export async function swrFetcher(url: string) {
  const res = await fetch(env.NEXT_PUBLIC_NESTJS_SERVER + url, {
    method: "GET",
    headers: {
      Authorization: "Bearer " + localStorage.getItem("token") || "",
    },
  });
  if ((await res.status) === 401) {
    localStorage.removeItem("token");
    window.location.replace("/");
  }
  const json = await res.json();
  return json;
}
