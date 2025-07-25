/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:48:06 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/25 16:30:30 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include "../mlx/mlx.h"
# include <fcntl.h>

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*mlx_img;

	void	*img_empty;
	void	*img_ennemy;
	void	*img_wall;
	void	*img_item;
	void	*img_exit;
	void	*img_start_player;

	int		nb_img_item;
	int		nb_img_exit;
	int		nb_img_start_character;
	int		nb_move;
	int		loop_anim_perso;
	int		loop_anim_ennemy;
	int		end;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		sens_perso;
	int		pos_perso;
	int		pos_ennemy;
	int		sens_ennemy;

	char	*relative_path;
	char	**map;
	int		img_width;
	int		img_height;
	int		win_width;
	int		win_height;
}	t_game;

char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int nb);
int		ft_strlen(const char *str);
int		check_arg(char *input);
char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);
int		ft_verif_n(char *str);
char	**read_map(char *input);
void	free_map(char **map);
int		check_map(t_game *game);
void	init_game(t_game *game);
void	set_window_size(t_game *game);
void	img_draw(t_game *game, void *image, int x, int y);
int		draw_map(t_game *game);
void	play(t_game *game);
void	destroy_all_img(t_game *game);
void	check_presskey(int key, t_game *game);
int		close_game(t_game *game);
void	draw_exit(t_game *game, int x, int y);
void	z_key_pressed(t_game *game);
void	q_key_pressed(t_game *game);
void	d_key_pressed(t_game *game);
void	s_key_pressed(t_game *game);
void	q_key_pressed2(t_game *game);
void	d_key_pressed2(t_game *game);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
void	print_moves(t_game *game);
void	ft_putchar(char c);
char	*ft_itoa(int nb);
void	animation_perso(t_game *game);
void	animation_ennemy(t_game *game);
void	perso_droit(t_game *game);
void	perso_droit1(t_game *game);
void	perso_droit2(t_game *game);
void	perso_droit3(t_game *game);
void	perso_gauche(t_game *game);
void	perso_gauche1(t_game *game);
void	perso_gauche2(t_game *game);
void	perso_gauche3(t_game *game);
void	ennemy_droit(t_game *game);
void	ennemy_droit1(t_game *game);
void	ennemy_droit2(t_game *game);
void	ennemy_droit3(t_game *game);
void	ennemy_gauche(t_game *game);
void	ennemy_gauche1(t_game *game);
void	ennemy_gauche2(t_game *game);
void	ennemy_gauche3(t_game *game);
void	print_moves_draw(t_game *game);
void	end_message_z(t_game *game);
void	end_message_q(t_game *game);
void	end_message_d(t_game *game);
void	end_message_s(t_game *game);

#endif