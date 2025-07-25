/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:03:59 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/11 15:27:51 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	is_min_stack(t_dlist *stack_a, int nb)
{
	int		head;
	t_list	*tmp;

	tmp = stack_a->begin;
	head = nb;
	while (tmp != NULL)
	{
		if (head > tmp->content)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	r_v(t_list *stack, int index)
{
	int		i;
	t_list	*tmp;

	tmp = stack;
	i = -1;
	while (index > ++i)
		tmp = tmp->next;
	return (tmp->content);
}

int	return_max_index(t_dlist *tmp)
{
	int	max;
	int	index_max;
	int	i;

	i = -1;
	max = -2147483648;
	index_max = 0;
	while (len_dlist(tmp) / 2 >= ++i)
	{
		if (r_v((tmp)->begin, i) > max)
		{
			index_max = i + 1;
			max = r_v((tmp)->begin, i);
		}
	}
	i = len_dlist(tmp);
	while (len_dlist(tmp) / 2 < --i)
	{
		if (r_v((tmp)->begin, i) > max)
		{
			index_max = i - len_dlist(tmp) + 1;
			max = r_v((tmp)->begin, i);
		}
	}
	return (index_max);
}

void	put_min_above(t_dlist **tmp, t_dlist **stack_a)
{
	int	min1;
	int	min2;
	int	i;

	i = -1;
	min1 = 2147483647;
	min2 = 2147483647;
	while (len_dlist(*tmp) / 2 >= ++i)
	{
		if (r_v((*tmp)->begin, i) < min1)
			min1 = r_v((*tmp)->begin, i);
	}
	i = len_dlist(*tmp);
	while (len_dlist(*tmp) / 2 < --i)
	{
		if (r_v((*tmp)->begin, i) < min2)
			min2 = r_v((*tmp)->begin, i);
	}
	if (min1 < min2)
		while (!is_min_stack(*tmp, (*tmp)->begin->content))
			move_ra(&*tmp, &*stack_a);
	else
		while (!is_min_stack(*tmp, (*tmp)->begin->content))
			move_rra(&*tmp, stack_a);
}

void	put_min_above_tmp(t_dlist **tmp, t_dlist **stack_a)
{
	int	min1;
	int	min2;
	int	i;

	i = -1;
	min1 = 2147483647;
	min2 = 2147483647;
	while (len_dlist(*tmp) / 2 >= ++i)
	{
		if (r_v((*tmp)->begin, i) < min1)
			min1 = r_v((*tmp)->begin, i);
	}
	i = len_dlist(*tmp);
	while (len_dlist(*tmp) / 2 < --i)
	{
		if (r_v((*tmp)->begin, i) < min2)
			min2 = r_v((*tmp)->begin, i);
	}
	if (min1 < min2)
		while (!is_min_stack(*tmp, (*tmp)->begin->content))
			move_ra_tmp(&*tmp, &*stack_a);
	else
		while (!is_min_stack(*tmp, (*tmp)->begin->content))
			move_rra_tmp(&*tmp, &*stack_a);
}
