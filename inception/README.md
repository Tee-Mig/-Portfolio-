# Projet Inception - Administration Système

Ce projet consiste à déployer une mini-infrastructure Docker complète dans une machine virtuelle, en utilisant **docker-compose**.

## Objectifs

- Construire et gérer plusieurs containers Docker dédiés (NGINX, WordPress + php-fpm, MariaDB).
- Utiliser des images basées sur l’avant-dernière version stable d’Alpine ou Debian.
- Assurer une communication sécurisée via NGINX avec TLSv1.2/1.3 sur le port 443.
- Mettre en place volumes persistants pour la base de données et les fichiers WordPress.
- Utiliser un docker-network dédié pour connecter les services.
- Automatiser le build et le déploiement via un Makefile.
- Respecter les bonnes pratiques Docker (pas de "hacky patch", variables d’environnement, pas de mots de passe en clair).

## Structure du projet

- `srcs/` : fichiers de configuration, Dockerfiles et docker-compose.yml
- `secrets/` : stockage sécurisé des informations sensibles
- Makefile à la racine pour build et lancer les services
