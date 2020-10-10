/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_djkastra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:06:35 by asmall            #+#    #+#             */
/*   Updated: 2020/08/28 18:06:36 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Initializing the final path structure
*/

static void		way_buld(t_path *path, int path_cost, t_way **ways)
{
	t_way		*way;

	if (!(way = (t_way *)malloc(sizeof(t_way))))
		ft_perror();
	init_way(way, path_cost, ways, path);
	if (*ways)
		(*ways)->prev = way;
	*ways = way;
}

/*
** We create an n-path structure with a name for the rooms and a pointer
** to the next and previous element.
*/

static void		init_path(t_path *path, t_room *room_p, t_path *tmp)
{
	path->room = room_p;
	path->next = tmp;
	path->prev = NULL;
	if (tmp)
		tmp->prev = path;
	else
		tmp->prev = tmp;
}

void			path(t_room *room, t_room *start, t_way **ways, int path_cost)
{
	t_path		*tmp;
	t_path		*path;
	t_room		*room_p;
	t_connect	*connect_p;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		ft_perror();
	path_cost = ft_init_path_struct(path, room, path_cost);
	while (room && room != start)
	{
		room_p = room->room_par;
		connect_p = room_p->connects;
		while (connect_p && connect_p->room != room)
			connect_p = connect_p->next;
		if (connect_p && connect_p->room == room)
		{
			tmp = path;
			if (!(path = (t_path *)malloc(sizeof(t_path))))
				ft_perror();
			init_path(path, room_p, tmp);
		}
		room = room->room_par;
	}
	way_buld(path, path_cost, ways);
}

/*
** The function counts the number of ants on each path
** ++way->ants: counting the number of ants passing through the path
*/

void			terms_staps(t_way *way, t_data *data, int steps, t_buf *buf)
{
	t_path		*path;

	path = way->path;
	while (path)
	{
		if (path->room == data->start && data->start->ant &&
			(way->path_cost <= steps || way->path_number == 1))
		{
			copy_text_buff(data, path, buf, ++data->ant);
			++way->ants;
		}
		else if (path->room != data->start && path->room != data->end
			&& path->room->ant)
			copy_text_buff(data, path, buf, path->room->ant);
		path = path->next;
	}
}

/*
** rooms_count: number of rooms.
** initially the list of visited nodes is empty, weight = 0.
*/

void			djkastra(int flag, t_data *data, int room_count)
{
	t_room		*room;
	t_connect	*connect;
	t_room		*room_d;

	while (--room_count && flag == 1)
	{
		flag = 0;
		room = data->rooms;
		if (room == data->end)
			room = room->next;
		while (room)
		{
			if (room->state)
			{
				if (room->weight != INF)
					connect = turn_and_change(room, connect,
											data->start, &flag);
				if ((room_d = room->out_part) && room_d->weight != INF)
					connect = turn_and_change(room_d, connect,
											data->start, &flag);
			}
			room = room->next;
			(room == data->end) ? room = room->next : 0;
		}
	}
}
