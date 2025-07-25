/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:20:30 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/10 13:41:38 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	print_stack_a(t_dlist *stack_a)
{
	t_list	*tmp;

	tmp = stack_a->begin;
	if (stack_a != NULL)
	{
		while (tmp->next != NULL)
		{
			printf("%d -> ", tmp->content);
			tmp = tmp->next;
		}
		printf("%d\n", tmp->content);
	}
}

void	print_stack_b(t_dlist *stack_b)
{
	t_list	*tmp;

	tmp = stack_b->begin;
	if (stack_b != NULL)
	{
		while (tmp->next != NULL)
		{
			printf("%d -> ", tmp->content);
			tmp = tmp->next;
		}
		printf("%d\n", tmp->content);
	}
}

void	print_stacks(t_dlist *stack_a, t_dlist *stack_b)
{
	if (stack_a != NULL)
		print_stack_a(stack_a);
	if (stack_b != NULL)
		print_stack_b(stack_b);
}

void	ft_print_stack(t_dlist *stack)
{
	t_list	*tmp;

	if (len_dlist(stack) == 0)
	{
		printf("Y'a rien garcon\n");
		return ;
	}
	tmp = stack->begin;
	while (tmp->next != NULL)
	{
		printf(" [%d] ->", tmp->content);
		tmp = tmp->next;
	}
	printf(" [%d]\n", tmp->content);
}
