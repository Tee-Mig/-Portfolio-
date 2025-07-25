/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:56:59 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/15 17:00:43 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	five_cases_spec2(t_dlist *stack_a)
{
	if (is_min_five(stack_a, stack_a->begin->content)
		&& is_max_five(stack_a, stack_a->begin->next->content))
	{
		if (stack_a->begin->next->next->content > stack_a->end->back->content
			&& stack_a->begin->next->next->content > stack_a->end->content
			&& stack_a->end->back->content < stack_a->begin->next->next->content
			&& stack_a->end->back->content > stack_a->end->content
			&& stack_a->end->content < stack_a->begin->next->next->content
			&& stack_a->end->content < stack_a->end->back->content)
			return (1);
	}
	return (0);
}

void	sort_five_spec(t_dlist **stack_a, t_dlist **stack_b)
{
	move_pb(&*stack_a, &*stack_b);
	move_pb(&*stack_a, &*stack_b);
	move_pb(&*stack_a, &*stack_b);
	move_sa(&*stack_a);
	move_pa(&*stack_a, &*stack_b);
	move_ra(&*stack_a, &*stack_b);
	move_pa(&*stack_a, &*stack_b);
	move_ra(&*stack_a, &*stack_b);
	move_pa(&*stack_a, &*stack_b);
	move_rra(&*stack_a, &*stack_b);
	move_rra(&*stack_a, &*stack_b);
}

void	sort_five_spec2(t_dlist **stack_a, t_dlist **stack_b)
{
	move_pb(&*stack_a, &*stack_b);
	move_pb(&*stack_a, &*stack_b);
	move_pb(&*stack_a, &*stack_b);
	move_ra(&*stack_a, &*stack_b);
	move_pa(&*stack_a, &*stack_b);
	move_ra(&*stack_a, &*stack_b);
	move_pa(&*stack_a, &*stack_b);
	move_ra(&*stack_a, &*stack_b);
	move_pa(&*stack_a, &*stack_b);
}
