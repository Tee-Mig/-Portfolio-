/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_last_to_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:08:36 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 15:09:17 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	move_rra(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_a == NULL || (*stack_a)->begin->next == NULL)
		return ;
	write(1, "rra\n", 4);
	ft_add_first(&*stack_a, (*stack_a)->end->content, &*stack_b);
	ft_remove_last_node(&*stack_a);
}

void	move_rrb(t_dlist **stack_b, t_dlist **stack_a)
{
	if (*stack_b == NULL || (*stack_b)->begin->next == NULL)
		return ;
	write(1, "rrb\n", 4);
	ft_add_first(&*stack_b, (*stack_b)->end->content, &*stack_a);
	ft_remove_last_node(&*stack_b);
}

void	move_rrr(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_a == NULL || (*stack_a)->begin->next == NULL
		|| *stack_b == NULL || (*stack_b)->begin->next == NULL)
		return ;
	write(1, "rrr\n", 4);
	ft_add_first(&*stack_a, (*stack_a)->end->content, &*stack_b);
	ft_remove_last_node(&*stack_a);
	ft_add_first(&*stack_b, (*stack_b)->end->content, &*stack_a);
	ft_remove_last_node(&*stack_b);
}

void	move_rra_tmp(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_a == NULL || (*stack_a)->begin->next == NULL)
		return ;
	ft_add_first(&*stack_a, (*stack_a)->end->content, &*stack_b);
	ft_remove_last_node(&*stack_a);
}
