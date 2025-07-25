# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 16:10:43 by mfaucheu          #+#    #+#              #
#    Updated: 2021/12/02 14:04:24 by mfaucheu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = ft_isdigit.c \
		ft_memset.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_isprint.c\
		ft_putchar_fd.c \
		ft_strlcat.c \
		ft_substr.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_putendl_fd.c\
		ft_strlcpy.c \
		ft_tolower.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_putnbr_fd.c \
		ft_strlen.c\
		ft_toupper.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_putstr_fd.c \
		ft_strmapi.c \
		ft_isalnum.c\
		ft_memcmp.c \
		ft_split.c \
		ft_strncmp.c \
		ft_isalpha.c \
		ft_strchr.c \
		ft_strnstr.c\
		ft_isascii.c \
		ft_memmove.c \
		ft_strdup.c \
		ft_strrchr.c \
		ft_striteri.c \

FILES_B = ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_lstmap.c \

OBJS = ${FILES:.c=.o}

OBJS_B	= ${FILES_B:.c=.o}

RM	= rm -f

CC	= gcc

AR	= ar rcs

NAME	= libft.a

CFLAGS	= -Wall -Werror -Wextra

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
				${AR} ${NAME} ${OBJS}

bonus:		${OBJS_B}
				${AR} ${NAME} ${OBJS_B}

clean:
			${RM} ${OBJS} ${OBJS_B}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re