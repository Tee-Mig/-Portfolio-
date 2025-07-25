NAME = cub3D

SRCS =	\
		src/bleed_fd.c\
		src/check_colors.c\
		src/check_map.c\
		src/collisions.c\
		src/controls.c\
		src/count_things.c\
		src/create_things.c\
		src/does_intersect.c\
		src/draw_image.c\
		src/draw_line.c\
		src/free_cub.c\
		src/free_things.c\
		src/free_things2.c\
		src/ft_atoi.c\
		src/ft_isdigit.c\
		src/ft_pow.c\
		src/ft_put_pixel.c\
		src/ft_split.c\
		src/ft_strchr.c\
		src/ft_strdup.c\
		src/ft_split_set.c\
		src/ft_strncmp.c\
		src/ft_strtrim.c\
		src/ft_substr.c\
		src/get_color_by_char.c\
		src/get_next_line_utils.c\
		src/get_next_line.c\
		src/get_things.c\
		src/init_cub.c\
		src/init_rays.c\
		src/init_render.c\
		src/is_space.c\
		src/line_is_map.c\
		src/line_is_spaces.c\
		src/main.c\
		src/make_map.c\
		src/map_contain_illegal_chars.c\
		src/mouse_controls.c\
		src/move_backward.c\
		src/move_forward.c\
		src/move_left.c\
		src/move_right.c\
		src/parsing.c\
		src/sprite_to_tab.c\
		src/sprite_to_tab2.c\
		src/ternaries.c\
		src/textures_are_null.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -g3

CC = cc

RM = rm -f

MLX_NAME = mlx_linux
DEPENDS := $(patsubst %.c,%.d,$(SRCS))

ifeq ($(MAKECMDGOALS), bonus)
	FLAGS += -D BONUS
	SRCS += src/move_doors.c src/draw_minimap.c src/draw_minimap2.c
endif
ifeq ($(MAKECMDGOALS), re_bonus)
	FLAGS += -D BONUS
	SRCS += src/move_doors.c src/draw_minimap.c src/draw_minimap2.c
endif
ifeq ($(MAKECMDGOALS), clean)
	FLAGS += -D BONUS
	SRCS += src/move_doors.c src/draw_minimap.c src/draw_minimap2.c
endif
ifeq ($(MAKECMDGOALS), fclean)
	FLAGS += -D BONUS
	SRCS += src/move_doors.c src/draw_minimap.c src/draw_minimap2.c
endif

all : $(NAME)

bonus: all

-include $(DEPENDS)
%.o: %.c Makefile
			$(CC) $(FLAGS) -MMD -MP -I/usr/include -I$(MLX_NAME) -c $< -o $@


$(NAME):	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -I$(MLX_NAME) -L$(MLX_NAME) -lXfixes -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)


clean :		
			${RM} $(OBJS)
			$(RM) $(DEPENDS)

fclean :	clean
			${RM} $(NAME)

re :		fclean all

re_bonus:	fclean all

.PHONY:		all bonus clean fclean re re_bonus
