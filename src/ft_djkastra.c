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
** Инициализация финальной структуры пути
*/

static void		create_way(t_path *path, int path_cost, t_way **ways)
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
** Создаем структуру n-пути с название на комнаты и указателем
** на следующий и предыдущий элемент.
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
	create_way(path, path_cost, ways);
}

/*
** turn_and_change: присваивание комнате вес
** path: создание n-части пути, инициализация структур t_way и t_path.
** null: возвращаем структуру к исходному состоянию weight.
** rooms_count: количество комнат; weight: временная метка.
** изначально список посещённых узлов пуст, weight = 0.
** начиная с узла-источника, все преемники текущего узла,
*/

void			djkastra(int flag, t_data *data)
{
	t_room		*room;
	t_connect	*connect;
	t_room		*room_d;

	while (--(data->rooms_count) && flag == 1)
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
