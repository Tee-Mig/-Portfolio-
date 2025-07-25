/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:39:50 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/02/20 18:05:28 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_lstclear(t_dlist **lst)
{
	t_list	*tmp;
	t_list	*pelem;

	pelem = (*lst)->begin;
	while (pelem)
	{
		tmp = pelem;
		pelem = pelem->next;
		free(tmp);
		(*lst)->length--;
	}
	(*lst)->begin = NULL;
	(*lst)->end = NULL;
}

void	ft_lstclear_node(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	ft_add_first(t_dlist **head, int val, t_dlist **head2)
{
	t_list	*nouv;

	nouv = malloc(sizeof(t_list));
	if (!nouv)
		free_stacks(&*head, &*head2);
	nouv->content = val;
	nouv->next = (*head)->begin;
	nouv->back = NULL;
	if ((*head)->begin)
		(*head)->begin->back = nouv;
	else
	{
		(*head)->length = 0;
		(*head)->end = nouv;
	}
	(*head)->begin = nouv;
	(*head)->length++;
}

void	ft_add_last(t_dlist **head, int val, t_dlist **head2)
{
	t_list	*nouv;

	nouv = malloc(sizeof(t_list));
	if (!nouv)
		free_stacks(&*head, &*head2);
	nouv->content = val;
	nouv->back = (*head)->end;
	nouv->next = NULL;
	if ((*head)->end)
		(*head)->end->next = nouv;
	else
	{
		(*head)->length = 0;
		(*head)->begin = nouv;
	}
	(*head)->end = nouv;
	(*head)->length++;
}

void	init_dlist(t_dlist **lst)
{
	(*lst)->begin = NULL;
	(*lst)->end = NULL;
}
