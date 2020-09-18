/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                          :+:      :+:    :+:   */
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

static void		change_cost(t_room *room, t_connect *connect, int *flag)
{
	connect->room->weight = room->weight + connect->weight;
	if (!connect->room->room_par ||
	((connect->room->room_par) && !loop(room, connect->room)))
	{
		connect->room->room_par = room;
		*flag = 1;
	}
}

/*
** изначально список посещённых узлов пуст, weight = 0.
** начиная с узла-источника, все преемники текущего узла,
** которые ещё не были посещены, пометить как посещённые (weight)
** change_cost: изменить временную метку (weight) на постоянную.
*/

t_connect		*turn_room(t_room *room, t_connect *connect,
			t_room *start, int *flag)
{
	connect = room->connects;
	while (connect)
	{
		if (room->weight + connect->weight < connect->room->weight
			&& connect->room != start)
			change_cost(room, connect, flag);
		connect = connect->next;
	}
	return (connect);
}
