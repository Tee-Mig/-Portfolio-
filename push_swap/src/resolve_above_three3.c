/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_above_three3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:23:33 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/08 14:31:19 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	c_min(t_dlist **ma, t_dlist **mb, t_dlist **stack_b, int *min_id)
{
	t_boucle	mv_min;

	mv_min.min_result = 2147483647;
	mv_min.i = -1;
	while (len_dlist(*stack_b) > ++mv_min.i)
	{
		if (r_v((*ma)->begin, mv_min.i) >= 0
			&& r_v((*mb)->begin, mv_min.i) >= 0)
		{
			if (r_v((*ma)->begin, mv_min.i) + r_v((*mb)->begin, mv_min.i)
				< mv_min.min_result)
				*min_id = min_move1(&mv_min.min_result, &*ma, &*mb, &mv_min.i);
		}
		else if (r_v((*ma)->begin, mv_min.i)
			< 0 && r_v((*mb)->begin, mv_min.i) < 0)
		{
			if ((r_v((*ma)->begin, mv_min.i) * -1)
				+ (r_v((*mb)->begin, mv_min.i) * -1)
				< mv_min.min_result)
				*min_id = min_move2(&mv_min.min_result, &*ma, &*mb, &mv_min.i);
		}
		else
			c_min2(&*ma, &*mb, &*min_id, &mv_min);
	}
}

int	min_move1(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i)
{
	*min_result = r_v((*move_a)->begin, *i);
	*min_result += r_v((*move_b)->begin, *i);
	return (*i);
}

int	min_move2(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i)
{
	*min_result = (r_v((*move_a)->begin, *i) * -1);
	*min_result += (r_v((*move_b)->begin, *i) * -1);
	return (*i);
}

void	c_min2(t_dlist **ma, t_dlist **mb, int *min_id, t_boucle *mv_min)
{
	if (r_v((*ma)->begin, mv_min->i) < 0)
	{
		if ((r_v((*ma)->begin, mv_min->i) * -1) + r_v((*mb)->begin, mv_min->i)
			< mv_min->min_result)
			*min_id = min_move3(&mv_min->min_result, &*ma, &*mb, &mv_min->i);
	}
	else if (r_v((*mb)->begin, mv_min->i) < 0)
	{
		if (r_v((*ma)->begin, mv_min->i) + (r_v((*mb)->begin, mv_min->i) * -1)
			< mv_min->min_result)
			*min_id = min_move4(&mv_min->min_result, &*ma, &*mb, &mv_min->i);
	}
}
