# push_swap

Projet 42 : Tri d'entiers dans une pile avec un nombre minimal d'opérations via un ensemble limité d'instructions.

## 🎯 Objectif

Écrire un programme `push_swap` qui trie une pile d’entiers (`pile a`) en utilisant uniquement des instructions spécifiques (`sa`, `pb`, `ra`, etc.), et en produisant **le moins d’opérations possible**.

## ✅ Contraintes

- Langage : C (norme 42)
- Libft autorisée
- Instructions autorisées : `sa`, `pb`, `ra`, `rr`, `rra`, etc.
- Aucune variable globale
- Makefile requis (`all`, `clean`, `fclean`, `re`)
- Gestion d'erreurs obligatoire

## 🎯 Performances attendues

- Trier 100 entiers en ≤ **700** instructions (moyenne)
- Trier 500 entiers en ≤ **5500** instructions (max)

## 🧨 Bonus (si partie obligatoire parfaite)

- Création d’un programme `checker` vérifiant que les instructions triées sont correctes
- Lecture des instructions via l'entrée standard

## ⚙️ Utilisation

```bash
ARG="2 1 3"; ./push_swap $ARG
./push_swap $ARG | ./checker $ARG
```
