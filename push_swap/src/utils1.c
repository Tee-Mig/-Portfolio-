/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:34:20 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/20 14:01:15 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	len_dlist(t_dlist *lst)
{
	if (lst == NULL)
		return (0);
	return (lst->length);
}

void	ft_remove_first_node(t_dlist **lst)
{
	t_list	*tmp;

	tmp = (*lst)->begin;
	if (!tmp)
		return ;
	(*lst)->begin = tmp->next;
	if ((*lst)->begin)
	{
		(*lst)->length--;
		(*lst)->begin->back = NULL;
	}
	else
	{
		(*lst)->length = 0;
		(*lst)->end = NULL;
	}
	free(tmp);
}

void	ft_remove_last_node(t_dlist **lst)
{
	t_list	*tmp;

	tmp = (*lst)->end;
	if (!tmp)
		return ;
	(*lst)->end = tmp->back;
	if ((*lst)->end)
	{
		(*lst)->length--;
		(*lst)->end->next = NULL;
	}
	else
	{
		(*lst)->length = 0;
		(*lst)->begin = NULL;
	}
	free(tmp);
}

int	is_empty_dlist(t_dlist *lst)
{
	if (lst == NULL)
		return (1);
	return (0);
}

int	is_sort(t_dlist *stack_a)
{
	int		nb_save;
	t_list	*tmp;

	if (len_dlist(stack_a) != 0)
	{
		tmp = stack_a->begin;
		nb_save = tmp->content;
		while (tmp != NULL)
		{
			if (nb_save > tmp->content)
				return (0);
			nb_save = tmp->content;
			tmp = tmp->next;
		}
		return (1);
	}
	return (0);
}
