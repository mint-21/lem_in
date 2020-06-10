/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turn.c                                          :+:      :+:    :+:   */
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
*/

static void	change_cost(t_room *room, t_link *link, int *flag)
{
	link->room->weight = room->weight + link->weight;
	if (!link->room->room_par ||
	((link->room->room_par) && !loop(room, link->room)))
	{
		link->room->room_par = room;
		*flag = 1;
	}
}

/*
** изначально список посещённых узлов пуст, weight = 0.
** начиная с узла-источника, все преемники текущего узла,
** которые ещё не были посещены, пометить как посещённые (weight)
** change_cost: изменить временную метку (weight) на постоянную.
*/

void		ft_turn(t_room *room, t_room *start, int *flag)
{
	t_link	*link;
	t_room	*room_d;

	if (room->weight != INF)
	{
		link = room->links;
		while (link)
		{
			if (room->weight + link->weight < link->room->weight
				&& link->room != start)
				change_cost(room, link, flag);
			link = link->next;
		}
	}
	if ((room_d = room->room_out) && room_d->weight != INF)
	{
		link = room_d->links;
		while (link)
		{
			if (room_d->weight + link->weight < link->room->weight
				&& link->room != start)
				change_cost(room_d, link, flag);
			link = link->next;
		}
	}
}
