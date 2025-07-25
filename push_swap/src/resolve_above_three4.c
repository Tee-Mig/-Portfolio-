/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_above_three4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:30:09 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/15 16:56:26 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	mv_min_id(int *min_id_mv, t_list **tmp_move_a, t_list **tmp_move_b)
{
	int	i;

	i = -1;
	while (*min_id_mv > ++i)
		*tmp_move_b = (*tmp_move_b)->next;
	i = -1;
	while (*min_id_mv > ++i)
		*tmp_move_a = (*tmp_move_a)->next;
}

void	mv_s1(t_list **ta, t_list **tb, t_dlist **stack_a, t_dlist **stack_b)
{
	while ((*ta)->content > 0 && (*tb)->content > 0)
	{
		(*ta)->content = ((*ta)->content) - 1;
		(*tb)->content = ((*tb)->content) - 1;
		move_rr(&*stack_a, &*stack_b);
	}
	while ((*ta)->content < 0 && (*tb)->content < 0)
	{
		(*ta)->content = ((*ta)->content) + 1;
		(*tb)->content = ((*tb)->content) + 1;
		move_rrr(&*stack_a, &*stack_b);
	}
	while ((*tb)->content > 0)
	{
		(*tb)->content = ((*tb)->content) - 1;
		move_rb(&*stack_b, &*stack_a);
	}
	mv_s2(&*ta, &*tb, &*stack_a, &*stack_b);
}

int	is_min_five(t_dlist *stack, int nb)
{
	t_list	*tmp;

	tmp = stack->begin;
	while (tmp != NULL)
	{
		if (tmp->content < nb)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	is_max_five(t_dlist *stack, int nb)
{
	t_list	*tmp;

	tmp = stack->begin;
	while (tmp != NULL)
	{
		if (tmp->content > nb)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	five_cases_spec(t_dlist *stack_a)
{
	if (is_min_five(stack_a, stack_a->begin->next->next->content)
		&& is_max_five(stack_a, stack_a->end->back->content))
	{
		if (stack_a->begin->content > stack_a->begin->next->content
			&& stack_a->begin->content < stack_a->end->content
			&& stack_a->begin->next->content < stack_a->begin->content
			&& stack_a->begin->next->content < stack_a->end->content
			&& stack_a->end->content > stack_a->begin->content
			&& stack_a->end->content > stack_a->begin->next->content)
			return (1);
	}
	return (0);
}
