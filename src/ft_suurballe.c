/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_suurballe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:27:26 by vfearles          #+#    #+#             */
/*   Updated: 2019/11/14 17:27:26 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Функция создает исходящие узлы
** ft_createroom: создаем структуру комнаты
** Вес ребер из исходящих во входящие узлы ставим на 0, наоборот -1
*/

static void	create_out_room(t_room *in, t_room *out, t_room *room)
{
	t_link	*link;

	out = ft_createroom(in->name);
	in->room_out = out;
	out->room_in = in;
	link = ft_createlink((room->room_out) ? room->room_out : room);
	link->weight = -1;
	link->room_one = in;
	out->links = in->links;
	in->links = link;
	link = out->links;
	while (link && link->room != room)
		link = link->next;
	if (link && link->room == room)
	{
		link->room = in;
		link->room_one = out;
		link->weight = 0;
	}
	else
		in->links = link;
}

/*
** Дублируем все промежуточные вершины найденного пути на входящие
** и исходящие узлы.
** create_out_room: создание исходящих узлов
** end изначально указывает на входящую часть и не перенаправляется
*/

static void	duplicate_rooms(t_path *path)
{
	t_room	*in;
	t_room	*out;
	t_link	*link;

	while (path)
	{
		if (!path->next || !path->next->next)
			return ;
		in = path->next->room;
		if (!in->room_out && !in->room_in)
			create_out_room(in, NULL, path->room);
		else if (in->room_out && !path->room->room_in)
		{
			out = path->room;
			link = in->links;
			while (link && link->room != out)
				link = link->next;
			if (link && link->room == out)
				link->room = out->room_out;
		}
		path = path->next;
	}
}

/*
** ft_dijkstra: поиск в ширину по алгоритму Дейкстры
** ft_direction: делаем график направленным и меняем направление ребер
** duplicate_rooms: дублируем все промежуточные вершины части пути во
** входящую и исходящую части.
*/

int			ft_suurballe(t_data *data)
{
	if (ft_dijkstra(data))
	{
		ft_direction(data->ways_dij->path);
		duplicate_rooms(data->ways_dij->path);
		return (1);
	}
	return (0);
}
