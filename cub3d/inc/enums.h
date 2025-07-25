/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:47:33 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 07:56:12 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_direction {north, south, east, west, none}	t_direction;
typedef enum e_pdirection {forward, backward, left, right}	t_pdirection;
typedef enum e_walltypes {wall, door, a_texture}	t_walltypes;
typedef enum e_doorstates {closed, opening, opened, closing}	t_doorstates;

enum e_keycodes
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_E = 101,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363
};

#endif
