/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_above_three2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:07:49 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 15:21:16 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	mv(t_dlist **mv_a, t_dlist **mv_b, t_dlist **s_a, t_dlist **s_b)
{
	t_mv	mv_index;

	mv_index.i = -1;
	while (len_dlist(*s_b) > ++mv_index.i)
	{
		mv_index.j = -1;
		cal_nb1(&mv_index.nb_filled, &mv_index.i, &*s_b, &*mv_b);
		while (len_dlist(*s_a) > ++mv_index.j)
		{
			if (mv_index.nb_filled == 0 && r_v((*s_b)->begin, mv_index.i)
				< (*s_a)->begin->content
				&&r_v((*s_b)->begin, mv_index.i) > (*s_a)->end->content)
				if_first(&*mv_a, &mv_index.nb_filled, &*s_a);
			mv_index.k = -1;
			mv2(&*s_a, &*s_b, &*mv_a, &mv_index);
			calcul_nb_move_max(&*mv_a, &*s_a, &mv_index.nb_filled);
		}
	}
}

void	cal_nb1(int *nb_filled, int *i, t_dlist **stack_b, t_dlist **move_b)
{
	*nb_filled = 0;
	if (*i <= len_dlist(*stack_b) / 2)
		ft_add_last(&*move_b, *i, &*stack_b);
	else
		ft_add_last(&*move_b, *i - len_dlist(*stack_b), &*stack_b);
}

void	if_first(t_dlist **move_a, int *nb_filled, t_dlist **stack_a)
{
	*nb_filled = 1;
	ft_add_last(&*move_a, 0, &*stack_a);
}

void	mv2(t_dlist **stack_a, t_dlist **stack_b, t_dlist **mv_a, t_mv *mv_id)
{
	if (mv_id->nb_filled == 0)
		while (len_dlist(*stack_a) / 2 > ++mv_id->k)
			if (r_v((*stack_b)->begin, mv_id->i)
				> r_v((*stack_a)->begin, mv_id->k)
				&& r_v((*stack_b)->begin, mv_id->i)
				< r_v((*stack_a)->begin, mv_id->k + 1))
				if_first_half(&*mv_a, &mv_id->nb_filled, &mv_id->k, &*stack_a);
	mv_id->k = len_dlist(*stack_a);
	if (mv_id->nb_filled == 0)
		while (len_dlist(*stack_a) / 2 < --mv_id->k)
			if (r_v((*stack_b)->begin, mv_id->i)
				< r_v((*stack_a)->begin, mv_id->k)
				&& r_v((*stack_b)->begin, mv_id->i)
				> r_v((*stack_a)->begin, mv_id->k - 1))
				if_end_half(&*mv_a, &*stack_a, &mv_id->nb_filled, &mv_id->k);
}

void	calcul_nb_move_max(t_dlist **move_a, t_dlist **stack_a, int *nb_filled)
{
	if (*nb_filled == 0)
	{
		ft_add_last(&*move_a, return_max_index(*stack_a), &*stack_a);
		*nb_filled = 1;
	}
}
