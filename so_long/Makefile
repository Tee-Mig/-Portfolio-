# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 16:42:02 by mfaucheu          #+#    #+#              #
#    Updated: 2022/02/25 16:27:25 by mfaucheu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	src/check_map.c \
		src/check_presskey.c \
		src/check_presskey2.c \
		src/check_presskey3.c \
		src/destroy_img.c \
		src/draw.c \
		src/ft_split.c \
		src/init_game.c \
		src/main.c \
		src/play.c \
		src/print_moves.c \
		src/read_map.c \
		src/utils.c \
		src/utils2.c \
		src/end_message.c

SRCS_BONUS =	src_bonus/check_map_bonus.c \
				src_bonus/check_presskey_bonus.c \
				src_bonus/check_presskey2_bonus.c \
				src_bonus/check_presskey3_bonus.c \
				src_bonus/destroy_img_bonus.c \
				src_bonus/draw_bonus.c \
				src_bonus/ft_split.c \
				src_bonus/init_game_bonus.c \
				src_bonus/main.c \
				src_bonus/play_bonus.c \
				src_bonus/print_moves.c \
				src_bonus/read_map_bonus.c \
				src_bonus/utils.c \
				src_bonus/utils2.c \
				src_bonus/ft_itoa.c \
				src_bonus/animation_perso.c \
				src_bonus/animation_perso2.c \
				src_bonus/animation_perso3.c \
				src_bonus/animation_ennemy.c \
				src_bonus/animation_ennemy2.c \
				src_bonus/animation_ennemy3.c \
				src_bonus/end_message.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror #fsanitize=address -g3

RM = rm -rf

NAME = so_long

NAME_BONUS = so_long_bonus

%.o: %.c
	$(CC) $(FLAGS) -I includes -Imlx -O3 -c $< -o $@

all :		$(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -Imlx -L/mlx -Lmlx -lmlx -lXext -lX11 -lm -lz -o $(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) $(OBJS_BONUS) -Imlx -L/mlx -Lmlx -lmlx -lXext -lX11 -lm -lz -o $(NAME_BONUS)

clean :
			${RM} ${OBJS} ${OBJS_BONUS}

fclean :	clean
			${RM} $(NAME) $(NAME_BONUS)

re :		fclean all

.PHONY:		all bonus clean fclean re
