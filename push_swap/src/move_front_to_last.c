/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_front_to_last.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:52:35 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 15:11:25 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	move_ra(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_a == NULL || (*stack_a)->begin->next == NULL)
		return ;
	write(1, "ra\n", 3);
	ft_add_last(&*stack_a, (*stack_a)->begin->content, &*stack_b);
	ft_remove_first_node(&*stack_a);
}

void	move_rb(t_dlist **stack_b, t_dlist **stack_a)
{
	if (*stack_b == NULL || (*stack_b)->begin->next == NULL)
		return ;
	write(1, "rb\n", 3);
	ft_add_last(&*stack_b, (*stack_b)->begin->content, &*stack_a);
	ft_remove_first_node(&*stack_b);
}

void	move_rr(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_a == NULL || (*stack_a)->begin->next == NULL
		|| *stack_b == NULL || (*stack_b)->begin->next == NULL)
		return ;
	write(1, "rr\n", 3);
	ft_add_last(&*stack_a, (*stack_a)->begin->content, &*stack_b);
	ft_remove_first_node(&*stack_a);
	ft_add_last(&*stack_b, (*stack_b)->begin->content, &*stack_a);
	ft_remove_first_node(&*stack_b);
}

void	move_ra_tmp(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_a == NULL || (*stack_a)->begin->next == NULL)
		return ;
	ft_add_last(&*stack_a, (*stack_a)->begin->content, &*stack_b);
	ft_remove_first_node(&*stack_a);
}
