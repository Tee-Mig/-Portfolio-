# Born2beRoot

## Description

Projet d’administration système visant à découvrir la virtualisation et à configurer un serveur sécurisé sur machine virtuelle (VirtualBox ou UTM). Installation d’un système Linux stable (Debian ou Rocky) avec règles strictes de sécurité et configuration minimale.

## Objectifs principaux

- Créer une VM avec Debian stable (conseillé) ou Rocky stable.
- Pas d’interface graphique installée.
- Configuration de partitions chiffrées avec LVM.
- Activation de SSH sur le port 4242, connexion root interdite.
- Mise en place d’un pare-feu (UFW ou firewalld) n’autorisant que le port 4242.
- Hostname au format `<login>42`.
- Politique stricte de mots de passe (complexité, expiration, avertissement).
- Configuration stricte de sudo (limitation des essais, journalisation, chemins restreints).
- Script bash `monitoring.sh` diffusant régulièrement des informations système.

## Rendu

Un seul fichier `signature.txt` contenant la signature SHA1 du disque virtuel (.vdi ou .qcow2) est à déposer sur le dépôt Git.  
La machine virtuelle elle-même ne doit pas être rendue.

---

Ce projet permet d’appréhender les bases de la virtualisation, la sécurisation d’un serveur Linux, et la gestion des services essentiels.
