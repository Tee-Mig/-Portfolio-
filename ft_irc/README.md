# ft_irc - Serveur IRC

## Objectif

Créer un serveur IRC en C++98 capable de gérer plusieurs clients simultanément avec un client IRC standard.

## Fonctionnalités obligatoires

- Serveur TCP non bloquant (poll ou équivalent unique)
- Authentification par mot de passe
- Commandes IRC essentielles : NICK, USER, JOIN, PRIVMSG
- Gestion des channels et opérateurs (KICK, INVITE, TOPIC, MODE)
- Transmission des messages à tous les membres d’un channel

## Contraintes techniques

- Pas de fork, pas de blocage I/O
- Compilation avec `-Wall -Wextra -Werror -std=c++98`
- Pas de bibliothèques externes ni Boost
- Utilisation exclusive des fonctions réseau standards (socket, bind, listen, accept, poll, send, recv...)

## Bonus (optionnel)

- Envoi de fichiers
- Bot IRC

## Utilisation

- Makefile avec règles `all, clean, fclean, re, $(NAME)`
