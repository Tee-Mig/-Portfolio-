/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:28:43 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 15:14:41 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_sort_three(t_dlist **stack_a, t_dlist **stack_b)
{
	t_list	*tmp;

	tmp = (*stack_a)->begin;
	if (tmp->content < tmp->next->content
		&& tmp->next->content > tmp->next->next->content
		&& tmp->content < tmp->next->next->content)
	{
		move_sa(&*stack_a);
		move_ra(&*stack_a, &*stack_b);
	}
	else if (tmp->content > tmp->next->content
		&& tmp->next->content < tmp->next->next->content
		&& tmp->content < tmp->next->next->content)
		move_sa(&*stack_a);
	else
		ft_sort_three2(&*stack_a, &*stack_b);
}

void	ft_sort_three2(t_dlist **stack_a, t_dlist **stack_b)
{
	t_list	*tmp;

	tmp = (*stack_a)->begin;
	if (tmp->content < tmp->next->content
		&& tmp->next->content > tmp->next->next->content
		&& tmp->content > tmp->next->next->content)
		move_rra(&*stack_a, &*stack_b);
	else if (tmp->content > tmp->next->content
		&& tmp->next->content < tmp->next->next->content
		&& tmp->content > tmp->next->next->content)
		move_ra(&*stack_a, &*stack_b);
	else if (tmp->content > tmp->next->content
		&& tmp->next->content > tmp->next->next->content
		&& tmp->content > tmp->next->next->content)
	{
		move_sa(&*stack_a);
		move_rra(&*stack_a, &*stack_b);
	}
}
