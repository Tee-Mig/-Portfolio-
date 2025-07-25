# ft_irc

IRC stands for Internet Chat Relay.Our project is creating our own IRC server acessible by an actual IRC client. Internet is ruled by solid standards protocols that allow connected computers to interact with each other. Let's discover this.

## Subject

We must use C++98.

- Our executable should run as follows : `./ircserv <port> <password>`.
- Communication between client(s) and server should be done via `TCP/IP` (v4 or/and v6).
- The server should be able to handle multiple clients at the same time and never hang.
- Forking isn't allowed. We should take advantage of the `poll()` function and all it's particularities and ressource usage advantages. And we should use `poll()` only and strictly once.
- We should be able to authenticate ()
- The server should forward messages to the suitable targets (channel members, private message target, ...).
- Our server should withstand absolutly every possible error :
  - Low Bandwith.
  - Network congestion.
  - Receiving partial data.
  - Memory exhaustion.
  - ...
- As using our server should ressemble using any traditionnal and official IRC server we have to implement the standard roles and commands :
  - **[Roles]** At least `Operators` and `Regular Users`.
  - **[Commands]** At least `KICK`, `INVITE`, `TOPIC`, `MODE (-t, -i, -k, -o, -l)`, `PRIVMSG`, `JOIN`, `NICK`, `PASS` ...

## Subject : bonus

- Implement a Bot.
- Handle file transfers.

# Compilation

make
