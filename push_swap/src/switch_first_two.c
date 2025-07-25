/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_first_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:06:11 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/08 14:31:40 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	swap_nodes(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	move_sa(t_dlist **stack_a)
{
	if ((*stack_a) == NULL || (*stack_a)->begin->next == NULL)
		return ;
	write(1, "sa\n", 3);
	swap_nodes(&(*stack_a)->begin->content, &(*stack_a)->begin->next->content);
}

void	move_sb(t_dlist **stack_b)
{
	if ((*stack_b) == NULL || (*stack_b)->begin->next == NULL)
		return ;
	write(1, "sb\n", 3);
	swap_nodes(&(*stack_b)->begin->content, &(*stack_b)->begin->next->content);
}

void	move_ss(t_dlist **stack_a, t_dlist **stack_b)
{
	if ((*stack_a) == NULL || (*stack_a)->begin->next == NULL
		|| (*stack_b) == NULL || (*stack_b)->begin->next == NULL)
		return ;
	write(1, "ss\n", 3);
	swap_nodes(&(*stack_a)->begin->content, &(*stack_a)->begin->next->content);
	swap_nodes(&(*stack_b)->begin->content, &(*stack_b)->begin->next->content);
}
