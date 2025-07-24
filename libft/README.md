# Libft

Projet 42 : création d'une bibliothèque C personnelle, `libft`, regroupant des fonctions utiles pour la suite du cursus.

## Fonctions obligatoires

- Fonctions standard de la libc (ex : `ft_strlen`, `ft_memcpy`, `ft_atoi`, etc.)
- Fonctions supplémentaires (ex : `ft_substr`, `ft_split`, `ft_itoa`, etc.)
- Affichage sur `file descriptor` (`ft_putchar_fd`, `ft_putstr_fd`, etc.)

## Partie bonus

Implémentation de fonctions de manipulation de **listes chaînées** (`t_list`).

## Contraintes

- Langage : C, norme 42
- Compilation : `-Wall -Wextra -Werror`
- Fichiers à la racine, Makefile avec règles `all`, `clean`, `fclean`, `re`, `bonus`
- Aucune fuite mémoire

## Utilisation

make

gcc main.c -L. -lft
