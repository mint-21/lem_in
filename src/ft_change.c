/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:01:12 by asmall            #+#    #+#             */
/*   Updated: 2020/07/28 18:01:13 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** the parent room is assigned the one whose weight is less than the current
*/

static int		loop(t_room *new_parrent, t_room *room)
{
	t_room		*ptr;

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
** mark visited rooms
** Weighting the current room (weight)
*/

t_connect		*turn_and_change(t_room *room, t_connect *connect,
			t_room *start, int *flag)
{
	connect = room->connects;
	while (connect)
	{
		if (room->weight + connect->weight < connect->room->weight
			&& connect->room != start)
		{
			connect->room->weight = room->weight + connect->weight;
			if (!connect->room->room_par ||
				((connect->room->room_par) && !loop(room, connect->room)))
			{
				connect->room->room_par = room;
				*flag = 1;
			}
		}
		connect = connect->next;
	}
	return (connect);
}
