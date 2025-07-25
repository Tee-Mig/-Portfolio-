/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:39:53 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 14:08:21 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define WIDTH 1280
# define HEIGHT 720
# define TILE 64
# define FOV 60

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>
# include "../mlx_linux/mlx_int.h"
# include <X11/extensions/Xfixes.h>
# include "../mlx_linux/mlx.h"
# include "structures.h"
# include "enums.h"
# include "get_next_line.h"

void	set_basic_windows_control(t_cub *cub);
void	ft_put_pixel(t_cubimg *img, int x, int y, int color);
void	draw_line(t_cubimg *img, t_point *start, t_point *end, int color);
t_point	*does_intersect(t_player *player, t_ray *ray, t_wall *wall);
int		draw(t_cub *cub);
t_point	*closest_intersection(t_player *player, t_ray *ray, t_wall *walls);
void	free_rays(t_ray	**rays);
void	free_walls(t_wall *walls);
void	init_rays(t_cub *cub);
int		xpm_to_sprite(t_sprite *tileset);
int		ft_isdigit(int c);
void	free_split(char **split);
char	**ft_split_set(char const *s, char *set);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
int		get_color_by_char(char ***colors, char *c, t_sprite *sprite);
int		hex_to_int(char *hex);
int		ft_pow(int x, int pow);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_int_split(int **split);
void	free_colors(char ***colors);
float	float_ternary(float condition, float true_value, float false_value);
int		int_ternary(int condition, int true_value, int false_value);
int		mouse_loop(t_cub *cub);
int		init_cub(t_cub *cub, char *path);
void	bleed_fd(int fd);
int		count_char_tab(char **tab);
void	init_render(size_t i, t_render *render, t_cub *cub);
int		check_boundaries(t_map *head);
void	make_map(t_map *m, t_cub *cub);
char	is_space(char c);
int		map_contain_illegal_chars(t_map *head);
void	free_cub(t_cub *cub);
int		will_collide(t_cub *cub, t_direction dir);
void	move_forward(t_cub *cub);
void	move_backward(t_cub *cub);
void	move_left(t_cub *cub);
void	move_right(t_cub *cub);
void	move_doors(t_wall *walls);
int		open_door(t_cub *cub);
char	put_info(t_cub *cub, char **info);
void	place_map_at_end(t_cub *cub, t_map *to_place);
char	check_colors(char **colors);
char	check_valid_rgb(char **colors);
void	free_walls(t_wall *walls);
void	free_player(t_player *p);
void	free_texture(t_sprite *t);
void	free_map(t_map *head);

t_point	*create_point(int x, int y);
t_wall	*create_wall(t_point *start, t_point *end,
			t_direction direction, t_walltypes type);
void	create_player(t_cub *cub, t_map *map, int x);

char	textures_are_null(t_cub *cub);

char	line_is_map(char *line);

char	line_is_spaces(char *line);

int		get_texture(char *texture, t_sprite **sprite);
int		get_color(int *x, char *s);
char	get_map(t_cub *cub, char *line, int fd);
int		get_infos(t_cub	*cub, int fd);
char	get_player(t_map *head, t_cub *cub);

int		**get_image(char ***colors, int fd, t_sprite *sprite);

void	draw_minimap(t_cub *cub);

size_t	get_xoffset(t_wall *head);
size_t	get_yoffset(t_wall *head);
float	get_xratio(t_wall *head);
float	get_yratio(t_wall *head);

#endif
