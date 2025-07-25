/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liste_chainee2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:53:25 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/31 10:53:56 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_last_node(t_dlist *lst)
{
	t_node	*tmp;
	t_node	*last_node;

	if (lst->size == 0)
		return ;
	tmp = lst->head;
	last_node = lst->head->next;
	if (lst->head->next == NULL)
	{
		lst->head = NULL;
		free(tmp);
	}
	else
	{
		while (last_node->next)
		{
			tmp = tmp->next;
			last_node = last_node->next;
		}
		tmp->next = NULL;
		free(last_node);
	}
	lst->size--;
}

void	free_list(t_dlist *lst)
{
	while (lst->size != 0)
		rm_last_node(lst);
}

void	del_node2(t_node *del, int idx, t_node *tmp, t_dlist *list)
{
	int	i;

	i = 1;
	while (i < idx - 1)
	{
		tmp = tmp->next;
		++i;
	}
	if (idx != list->size)
	{
		del = tmp->next;
		tmp->next = del->next;
		free(del);
		list->size--;
	}
	else if (idx == list->size)
	{
		del = tmp->next;
		tmp->next = NULL;
		list->end = tmp;
		free(del);
		list->size--;
	}
}

int	del_node(t_dlist *list, int idx)
{
	t_node	*tmp;
	t_node	*del;

	if (!list || idx < 0 || idx > list->size)
		return (0);
	tmp = list->head;
	del = tmp->next;
	if (idx == 1)
	{
		list->head = tmp->next;
		free(tmp);
		list->size--;
	}
	else
		del_node2(del, idx, tmp, list);
	return (1);
}
