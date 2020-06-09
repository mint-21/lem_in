/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_weight.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:01:12 by vfearles          #+#    #+#             */
/*   Updated: 2019/11/28 18:01:13 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	loop(t_room *new_parrent, t_room *room)
{
	t_room	*ptr;

	ptr = new_parrent;
	while (ptr)
	{
		if (ptr == room)
			return (1);
		ptr = ptr->room_par;
	}
	return (0);
}

/*
** Присваиваем текущей комнате вес (weight)
** loop: родительской комнатой назначается та, чей weight меньше текущего
** изначально список посещённых узлов пуст, weight = 0.
** начиная с узла-источника, все преемники текущего узла,
** которые ещё не были посещены, пометить как посещённые (weight)
** change_weight: изменить временную метку (weight) на постоянную.
*/

void	change_weight(t_room *room, t_room *start, int *flag)
{
	t_link	*link;

	link = room->links;
	while (link)
	{
		if (room->weight + link->weight < link->room->weight
				&& link->room != start)
		{
			link->room->weight = room->weight + link->weight;
			if (!link->room->room_par ||
			((link->room->room_par) && !loop(room, link->room)))
			{
				link->room->room_par = room;
				*flag = 1;
			}
		}
		link = link->next;
	}
}
