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
** Зануляем room_par и weight ставим на временную метку
*/

static void		null(t_room *room)
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
** Дублируем все промежуточные вершины найденного пути на входящие
** и исходящие узлы.
** create_out_room: создание исходящих узлов
** end изначально указывает на входящую часть и не перенаправляется
*/

static void		duplicate_rooms(t_path *path)
{
	t_room		*in;

	while (path)
	{
		if (!path->next || !path->next->next)
			return ;
		in = path->next->room;
		ft_creat_duplicate(path, in);
		path = path->next;
	}
}

/*
** ft_find_null: находим комнаты для обратных ребер и удаляем их связи
** ft_redirection_connect: перенаправление связей в структуре two
*/

void			ft_change_ribs(t_path *path)
{
	t_connect	*connect;

	while (path && path->next)
	{
		ft_find_null(path);
		connect = path->room->connects;
		while (connect && connect->room != path->next->room)
			connect = connect->next;
		if (connect && connect->room == path->next->room)
		{
			redirection_conditions(connect, path->room);
			ft_redirection_connect(path->room, path->next->room, connect);
		}
		path = path->next;
	}
}

static int		ft_ford(t_data *data, int flag, int k)
{
	data->start->weight = 0;
	djkastra(flag, k, data);
	if (!data->end->room_par)
		return (0);
	path(data->end, data->start, &data->ways_dij, 0);
	null(data->rooms);
	return (1);
}


/*
** ft_ford: поиск в ширину по алгоритму Дейкстры
** ft_change_ribs: делаем график направленным и меняем направление ребер
** duplicate_rooms: дублируем все промежуточные вершины части пути во
** входящую и исходящую части.
*/

int				ft_suurballe(t_data *data)
{
	int flag;
	int k;

	flag = 1;
	k = data->rooms_count;
	if (ft_ford(data, flag, k))
	{
		ft_change_ribs(data->ways_dij->path);
		duplicate_rooms(data->ways_dij->path);
		return (1);
	}
	return (0);
}
