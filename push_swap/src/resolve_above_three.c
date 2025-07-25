/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_above_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:04:33 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/20 17:27:36 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_sort_above_three(t_dlist **stack_a, t_dlist **stack_b)
{
	int		*lis;
	int		min_index_move;
	t_dlist	*tmp;
	int		i;

	lis = malloc(sizeof(int) * len_dlist(*stack_a));
	malloc_error_lis(lis, &*stack_a, &*stack_b);
	tmp = malloc(sizeof(t_dlist));
	tmp->begin = NULL;
	tmp->end = NULL;
	malloc_error_tmp(lis, &*stack_a, &*stack_b, &tmp);
	min_index_move = 0;
	i = -1;
	while (len_dlist(*stack_a) > ++i)
		ft_add_last(&tmp, r_v((*stack_a)->begin, i), &*stack_a);
	put_min_above_tmp(&tmp, &*stack_a);
	fill_lis_table(lis, &tmp);
	fill_lis_one_two(lis, &tmp);
	apply_lis(lis, &*stack_a, &*stack_b, tmp);
	res_ab32(&*stack_a, &*stack_b, &min_index_move);
	put_min_above(&*stack_a, &*stack_b);
	free(lis);
	ft_lstclear(&tmp);
	free(tmp);
}

void	res_ab32(t_dlist **stack_a, t_dlist **stack_b, int *min_index_move)
{
	t_dlist	*move_a;
	t_dlist	*move_b;
	t_list	*tmp_move_a;
	t_list	*tmp_move_b;

	move_a = malloc(sizeof(t_dlist));
	move_b = malloc(sizeof(t_dlist));
	init_dlist(&move_a);
	init_dlist(&move_b);
	while (len_dlist(*stack_b) > 0)
	{	
		mv(&move_a, &move_b, &*stack_a, &*stack_b);
		c_min(&move_a, &move_b, &*stack_b, &*min_index_move);
		tmp_move_a = move_a->begin;
		tmp_move_b = move_b->begin;
		mv_min_id(&*min_index_move, &tmp_move_a, &tmp_move_b);
		mv_s1(&tmp_move_a, &tmp_move_b, &*stack_a, &*stack_b);
		move_pa(&*stack_a, &*stack_b);
		ft_lstclear(&move_a);
		ft_lstclear(&move_b);
	}
	free(move_a);
	free(move_b);
}

void	fill_lis_table(int *lis, t_dlist **stack_a)
{
	int	i;
	int	j;

	i = -1;
	while (len_dlist(*stack_a) > ++i)
		lis[i] = 1;
	i = -1;
	while (len_dlist((*stack_a)) > ++i)
	{
		j = -1;
		while (i > ++j)
			if (r_v((*stack_a)->begin, i)
				> r_v((*stack_a)->begin, j))
				if (lis[i] < (lis[j] + 1))
					lis[i] = lis[j] + 1;
	}
}

void	fill_lis_one_two(int *lis, t_dlist **stack_a)
{
	int	max;
	int	i;

	i = -1;
	max = 0;
	while (len_dlist(*stack_a) > ++i)
	{
		if (lis[i] > max)
			max = lis[i];
	}
	i = len_dlist(*stack_a);
	while (--i >= 0)
	{
		if (lis[i] == max)
		{
			lis[i] = -1;
			max--;
		}
		else
			lis[i] = -2;
	}
}

void	apply_lis(int *lis, t_dlist **stack_a, t_dlist **stack_b, t_dlist *tmp)
{
	int		len_stack_a;
	int		i;
	int		j;
	t_dlist	*tmp_a;

	tmp_a = *stack_a;
	len_stack_a = len_dlist(*stack_a);
	i = -1;
	while (len_stack_a > ++i)
	{
		j = -1;
		while (r_v(tmp_a->begin, 0) != r_v(tmp->begin, ++j))
			;
		if (lis[j] == -2)
			move_pb(&tmp_a, &*stack_b);
		else
			move_ra(&tmp_a, &*stack_a);
	}
}
