/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:00:00 by vfearles          #+#    #+#             */
/*   Updated: 2019/12/04 17:00:01 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Удаление обратных краев(ребер) вместе с их оригиналами
*/

void		null_turn(t_connect *turn_head, t_connect *turn_tail, t_room *end)
{
	turn_head = end->connects;
	while (turn_head && turn_head->weight != -1)
		turn_head = turn_head->next;
	while (turn_head)
	{
		turn_tail = turn_head->turn_next;
		turn_head->turn_next = NULL;
		turn_head->parrent = NULL;
		turn_head = turn_tail;
	}
}

/*
** Удаление предыдущих связей в следующей связующей комнате,
** чтобы граф не был двунаправленным.
*/

static void	ft_null_connect(t_room *dst, t_room *src)
{
	t_connect	*connect;

	connect = dst->connects;
	while (connect && connect->room != src)
		connect = connect->next;
	if (connect && connect->room == src)
	{
		if (connect->prev)
			connect->prev->next = connect->next;
		else
			dst->connects = connect->next;
		if (connect->next)
			connect->next->prev = connect->prev;
		free(connect);
	}
}

/*
** path->room: комната со связями; path->next->room: следующая связующая комната.
** ft_null_connect: удаление предыдущих связей
*/

void  ft_find_null(t_path *path)
{
	t_room	*room_one;
	t_room	*room_two;

	room_one = path->room;
	room_two = path->next->room;
	if (!(room_one->in_part || room_one->out_part))
	{
		if (!(room_two->in_part || room_two->out_part))
			ft_null_connect(room_two, room_one);
		else if (room_two->out_part)
			ft_null_connect(room_two->out_part, room_one);
		else if (room_two->in_part)
			ft_null_connect(room_two->in_part, room_one);
	}
	else if (!(room_two->in_part || room_two->out_part))
	{
		if (room_one->in_part)
			ft_null_connect(room_two, room_one->in_part);
		else if (room_one->out_part)
			ft_null_connect(room_two, room_one->out_part);
	}
}
