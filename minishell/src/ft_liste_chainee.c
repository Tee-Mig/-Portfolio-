/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liste_chainee.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:10:57 by mfaucheu          #+#    #+#             */
/*   Updated: 2022/05/31 10:54:16 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dlist	*ft_lstnew(void)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (new != NULL)
	{
		new->size = 0;
		new->head = NULL;
	}
	return (new);
}

int	add_last(t_dlist *lst, void *elem)
{
	t_node	*new;

	if (!lst)
		return (0);
	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->content = elem;
	new->status = NULL;
	new->next = NULL;
	if (lst->head == NULL)
	{
		lst->end = new;
		lst->head = new;
	}
	else
	{
		lst->end->next = new;
		lst->end = new;
	}
	lst->size++;
	return (1);
}
