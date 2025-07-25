/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfaucheu <mfaucheu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:41:12 by mfaucheu          #+#    #+#             */
/*   Updated: 2021/12/02 14:38:37 by mfaucheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_cell;

	new_cell = ft_lstnew(f(lst->content));
	if (!new_cell)
	{
		ft_lstclear(&new_lst, del);
		return (NULL);
	}
	new_lst = new_cell;
	lst = lst->next;
	while (lst)
	{
		new_cell = ft_lstnew(f(lst->content));
		if (!(new_cell->content))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_cell);
		lst = lst->next;
	}
	return (new_lst);
}
