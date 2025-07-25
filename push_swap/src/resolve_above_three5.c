/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_above_three5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 22:41:55 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 15:20:43 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	if_end_half(t_dlist **mv_a, t_dlist **stack_a, int *nb_filled, int *k)
{
	*nb_filled = 1;
	ft_add_last(&*mv_a, *k - len_dlist(*stack_a), &*stack_a);
}

void	if_first_half(t_dlist **move_a, int *nb_filled, int *k, t_dlist **sa)
{
	*nb_filled = 1;
	ft_add_last(&*move_a, *k + 1, &*sa);
}

void	mv_s2(t_list **ta, t_list **tb, t_dlist **stack_a, t_dlist **stack_b)
{
	while ((*tb)->content < 0)
	{
		(*tb)->content = ((*tb)->content) + 1;
		move_rrb(&*stack_b, &*stack_a);
	}
	while ((*ta)->content > 0)
	{
		(*ta)->content = ((*ta)->content) - 1;
		move_ra(&*stack_a, &*stack_b);
	}
	while ((*ta)->content < 0)
	{
		(*ta)->content = ((*ta)->content) + 1;
		move_rra(&*stack_a, &*stack_b);
	}
}

int	min_move3(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i)
{
	*min_result = (r_v((*move_a)->begin, *i) * -1);
	*min_result += r_v((*move_b)->begin, *i);
	return (*i);
}

int	min_move4(int *min_result, t_dlist **move_a, t_dlist **move_b, int *i)
{
	*min_result = r_v((*move_a)->begin, *i);
	*min_result += (r_v((*move_b)->begin, *i) * -1);
	return (*i);
}
