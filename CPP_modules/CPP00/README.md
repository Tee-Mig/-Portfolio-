# C++ - Module 00

## Description

Introduction à la programmation orientée objet en C++98. Ce module couvre les bases : namespaces, classes, fonctions membres, streams stdio, listes d’initialisation, static, const, etc.

## Objectifs

- Compiler le code avec `-Wall -Wextra -Werror -std=c++98`
- Appliquer les bonnes pratiques C++ (pas de C, pas de mémoire non libérée)
- Implémenter trois exercices :
  - **ex00 : Mégaphone** — afficher les arguments en majuscules
  - **ex01 : PhoneBook** — gérer un répertoire limité à 8 contacts sans allocation dynamique
  - **ex02 : Account** — recréer un fichier manquant basé sur un journal de tests (facultatif)
- Respecter les interdictions : pas de `printf`, pas d’`alloc()`, pas de `using namespace`, pas de STL (vector, list, map...)

## Consignes générales

- Nommer dossiers ex00, ex01, ex02
- Fichiers et classes selon le format UpperCamelCase
- Code propre et lisible
- Gérer la mémoire correctement
- Soumettre uniquement les fichiers demandés

## 🛠️ Compilation

Utiliser :

c++ -Wall -Wextra -Werror -std=c++98 main.cpp
