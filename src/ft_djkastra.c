/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ford.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:06:35 by vfearles          #+#    #+#             */
/*   Updated: 2019/11/28 18:06:36 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Инициализация финальной структуры пути
*/

static void	create_way(t_path *path, int path_cost, t_way **ways)
{
	t_way	*way;

	if (!(way = (t_way *)malloc(sizeof(t_way))))
		ft_perror();
	init_way(way, path_cost, ways, path);
	if (*ways)
		(*ways)->prev = way;
	*ways = way;
}

/*
** Создаем структуру n-пути с название на комнаты и указателем
** на следующий и предыдущий элемент.
*/

static void		init_path(t_path *path, t_room *room_p, t_path *tmp)
{
	path->room = room_p;
	path->next = tmp;
	path->prev = NULL;
	(tmp->prev) = (tmp) ? (path) : (tmp);
}

void		path(t_room *room, t_room *start, t_way **ways, int path_cost)
{
	t_path		*tmp;
	t_path		*path;
	t_room		*room_p;
	t_connect	*connect_p;

	(!(path = (t_path *)malloc(sizeof(t_path)))) ? ft_perror() : 0;
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
			(!(path = (t_path *)malloc(sizeof(t_path)))) ? ft_perror() : 0;
			init_path(path, room_p, tmp);
		}
		room = room->room_par;
	}
	create_way(path, path_cost, ways);
}

/*
** turn_room: алгоритм поиска в ширину, назначение родительских узлов.
** path: создание n-части пути, инициализация структур t_way и t_path.
** null: возвращаем структуру к исходному состоянию weight.
** rooms_count = k: количество комнат; weight: временная метка.
*/

void		djkastra(int flag, int k, t_data *data)
{
	t_room		*room;
	t_connect	*connect;
	t_room		*room_d;

	while (--k && flag == 1)
	{
		flag = 0;
		room = data->rooms;
		(room == data->end) ? room = room->next : 0;
		while (room)
		{
			if (room->state)
			{
				if (room->weight != INF)
					connect = turn_room(room, connect, data->start, &flag);
				if ((room_d = room->out_part) && room_d->weight != INF)
					connect = turn_room(room_d, connect, data->start, &flag);
			}
			room = room->next;
			(room == data->end) ? room = room->next : 0;
		}
	}
}
