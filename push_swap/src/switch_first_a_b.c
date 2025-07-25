/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_first_a_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:36:42 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 15:12:19 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	move_pa(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_b != NULL)
	{
		write(1, "pa\n", 3);
		ft_add_first(&*stack_a, (*stack_b)->begin->content, &*stack_b);
		ft_remove_first_node(&*stack_b);
	}
}

void	move_pb(t_dlist **stack_a, t_dlist **stack_b)
{
	if (*stack_a != NULL)
	{
		write(1, "pb\n", 3);
		ft_add_first(&*stack_b, (*stack_a)->begin->content, &*stack_a);
		ft_remove_first_node(&*stack_a);
	}
}
