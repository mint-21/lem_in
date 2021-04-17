/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:01:12 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 14:32:07 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** mark visited rooms
** the parent room is assigned the one whose weight is less than the current
** Weighting the current room (weight)
*/

t_connect	*turn_and_change(t_room *room, t_connect *connect,
			t_room *start, int *flag)
{
	t_room		*ptr;

	connect = room->connects;
	ptr = room;
	while (connect)
	{
		if (room->weight + connect->weight < connect->room->weight
			&& connect->room != start)
		{
			connect->room->weight = room->weight + connect->weight;
			if (!connect->room->room_par || ((connect->room->room_par)))
			{
				while (ptr)
				{
					if (ptr == room)
						break ;
					ptr = ptr->room_par;
				}
				connect->room->room_par = room;
				*flag = 1;
			}
		}
		connect = connect->next;
	}
	return (connect);
}
