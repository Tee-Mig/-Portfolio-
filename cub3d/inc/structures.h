/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:33:57 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 15:00:26 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "enums.h"

typedef struct s_cubimg
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_cubimg;

typedef struct s_calculate
{
	float	x1;
	float	x2;
	float	x3;
	float	x4;
	float	y1;
	float	y2;
	float	y3;
	float	y4;
}	t_calculate;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_wall	t_wall;

typedef struct s_ray
{
	float	angle;
	float	distance;
	float	dirx;
	float	diry;
	t_point	*intersection;
	t_wall	*wall;
}	t_ray;

typedef struct s_player
{
	t_point	*pos;
	float	angle;	
}	t_player;

typedef struct s_sprite{
	char	*path;
	size_t	height;
	size_t	width;
	int		**img;
	size_t	char_per_pixel;
}	t_sprite;

typedef struct render
{
	float		wally;
	float		wallx;
	float		line_h;
	float		stepx;
	float		stepy;
	float		wallstart;
	float		wallend;
	t_sprite	*sprite;
}	t_render;

typedef struct s_map{
	char			*line;
	int				y;
	struct s_map	*next;
	struct s_map	*prev;
}	t_map;

# ifdef BONUS

typedef struct s_wall
{
	int				height;
	int				width;
	t_point			*start;
	t_point			*end;
	t_direction		direction;
	t_walltypes		type;
	t_doorstates	state;
	float			offsetx;
	float			offsety;			
	struct s_wall	*next;
}	t_wall;
typedef struct s_cub
{
	t_xvar		*mlx;
	t_win_list	*mlx_win;
	t_cubimg	*img;
	t_player	*player;

	t_sprite	*no_texture;
	t_sprite	*so_texture;
	t_sprite	*we_texture;
	t_sprite	*ea_texture;
	t_sprite	*do_texture;
	int			floor_color;
	int			ceiling_color;

	t_map		*m_head;

	t_ray		**rays;
	t_wall		*w_head;
}	t_cub;

# else

typedef struct s_wall
{
	int				height;
	int				width;
	t_point			*start;
	t_point			*end;
	t_direction		direction;
	t_walltypes		type;
	struct s_wall	*next;
}	t_wall;
typedef struct s_cub
{
	t_xvar		*mlx;
	t_win_list	*mlx_win;
	t_cubimg	*img;
	t_player	*player;

	t_sprite	*no_texture;
	t_sprite	*so_texture;
	t_sprite	*we_texture;
	t_sprite	*ea_texture;
	int			floor_color;
	int			ceiling_color;

	t_map		*m_head;

	t_ray		**rays;
	t_wall		*w_head;
}	t_cub;
# endif

typedef struct s_minimap
{
	float	xratio;
	float	yratio;
	size_t	offsetx;
	size_t	offsety;
}	t_minimap;

#endif 
