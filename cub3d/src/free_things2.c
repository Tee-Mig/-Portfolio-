/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccambium <ccambium@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:55:52 by ccambium          #+#    #+#             */
/*   Updated: 2022/11/29 11:41:33 by ccambium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	free_map(t_map *head)
{
	t_map	*ptr;

	if (head == NULL)
		return ;
	while (head)
	{
		ptr = head->next;
		free(head->line);
		free(head);
		head = ptr;
	}
}

void	free_texture(t_sprite *t)
{
	if (t->path)
		free(t->path);
	if (t->img)
		free_int_split(t->img);
	free(t);
}

void	free_player(t_player *p)
{
	if (p->pos)
		free(p->pos);
	free(p);
}
