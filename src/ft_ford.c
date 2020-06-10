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
** Зануляем room_par и weight ставим на временную метку
*/

static void	null(t_room *room)
{
	while (room)
	{
		if (room->state)
		{
			room->room_par = NULL;
			room->weight = INF;
			if (room->out_part)
			{
				room->out_part->room_par = NULL;
				room->out_part->weight = INF;
			}
			else if (room->in_part)
			{
				room->in_part->room_par = NULL;
				room->in_part->weight = INF;
			}
		}
		room = room->next;
	}
}

/*
** Инициализация финальной структуры пути
*/

static void	create_way(t_path *path, int path_cost, t_way **ways)
{
	t_way	*way;

	if (!(way = (t_way *)malloc(sizeof(t_way))))
		ft_perror();
	way->path = path;
	way->path_number = (*ways) ? (*ways)->path_number + 1 : 1;
	way->path_cost = path_cost;
	way->ants = 0;
	way->prev = NULL;
	way->next = *ways;
	if (*ways)
		(*ways)->prev = way;
	*ways = way;
}

int			ft_init_path_struct(t_path *path, t_room *room, int path_cost)
{
	path_cost = room->weight;
	path->room = room;
	path->next = NULL;
	path->prev = NULL;
	return (path_cost);
}

/*
** Создаем структуру n-пути с название на комнаты и указателем
** на следующий и предыдущий элемент.
*/

static void	path(t_room *room, t_room *start, t_way **ways, int path_cost)
{
	t_path	*tmp;
	t_path	*path;
	t_room	*room_p;
	t_link	*link_p;

	(!(path = (t_path *)malloc(sizeof(t_path)))) ? ft_perror() : 0;
	path_cost = ft_init_path_struct(path, room, path_cost);
	while (room && room != start)
	{
		room_p = room->room_par;
		link_p = room_p->links;
		while (link_p && link_p->room != room)
			link_p = link_p->next;
		if (link_p && link_p->room == room)
		{
			tmp = path;
			(!(path = (t_path *)malloc(sizeof(t_path)))) ? ft_perror() : 0;
			path->room = room_p;
			path->next = tmp;
			path->prev = NULL;
			(tmp->prev) = (tmp) ? (path) : (tmp);
		}
		room = room->room_par;
	}
	create_way(path, path_cost, ways);
}

/*
** ft_turn: алгоритм поиска в ширину, назначение родительских узлов.
** path: создание n-части пути, инициализация структур t_way и t_path.
** null: возвращаем структуру к исходному состоянию weight.
** rooms_count: количество комнат; weight: временная метка.
*/

int			ft_ford(t_data *data)
{
	int		k;
	t_room	*room;
	int		flag;

	k = data->rooms_count;
	flag = 1;
	data->start->weight = 0;
	while (--k && flag == 1)
	{
		flag = 0;
		room = data->rooms;
		(room == data->end) ? room = room->next : 0;
		while (room)
		{
			if (room->state)
				ft_turn(room, data->start, &flag);
			room = room->next;
			(room == data->end) ? room = room->next : 0;
		}
	}
	if (!data->end->room_par)
		return (0);
	path(data->end, data->start, &data->ways_dij, 0);
	null(data->rooms);
	return (1);
}
