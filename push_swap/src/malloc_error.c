/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:15:47 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/21 11:36:06 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	init_dlist_begin(t_dlist **lst1, t_dlist **lst2)
{
	if (!*lst1)
		exit(1);
	(*lst1)->begin = NULL;
	(*lst1)->end = NULL;
	(*lst1)->length = 0;
	if (!*lst2)
	{
		free(*lst1);
		exit(1);
	}
	(*lst2)->begin = NULL;
	(*lst2)->end = NULL;
	(*lst2)->length = 0;
}

void	malloc_error_lis(int *lis, t_dlist **stack_a, t_dlist **stack_b)
{
	if (!lis)
	{
		free(*stack_a);
		free(*stack_b);
		exit(1);
	}
}

void	malloc_error_tmp(int *lis, t_dlist **s_a, t_dlist **s_b, t_dlist **tmp)
{
	if (!*tmp)
	{
		free(*s_a);
		free(*s_b);
		free(lis);
		exit(1);
	}
	(*tmp)->begin = NULL;
	(*tmp)->end = NULL;
}

void	free_stacks(t_dlist **stack1, t_dlist **stack2)
{
	ft_lstclear(&*stack1);
	ft_lstclear(&*stack2);
	free(*stack1);
	free(*stack1);
	exit(1);
}
