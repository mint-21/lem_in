/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ways_ascending.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:56:17 by vfearles          #+#    #+#             */
/*   Updated: 2019/12/04 16:56:18 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Создаем структуру путей ways
** create_inhead: создаем входящие узлы
** находим кратчайшие пути в новом графе с их весом
*/

static void			path_init(t_path *path, t_room *end, t_path *tmp)
{
	path->room = end;
	path->next = tmp;
	path->prev = NULL;
}

static t_way		*ft_add_path(t_connect *head, t_way *ways, t_room *end)
{
	t_path		*path;
	t_way		*way;
	t_path		*tmp;
	int			weight;

	weight = 0;
	path = NULL;
	while (head)
	{
		tmp = path;
		if (!(path = (t_path *)malloc(sizeof(t_path))))
			ft_perror();
		head = create_inhead(tmp, path, head, &weight);
	}
	tmp = path;
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		ft_perror();
	path_init(path, end, tmp);
	if (tmp)
		tmp->prev = path;
	if (!(way = (t_way *)malloc(sizeof(t_way))))
		ft_perror();
	way = way_init(way, path, weight, ways);
	ways = way;
	return (ways);
}

/*
** Находим кратчайшие пути на новом графе и заносим в структуру
** ft_add_path: создание новой структуры для кратчайших путей
** Переворачиваем ребра от конца до старта и ищем пути
*/

t_way			*ft_ways_ascending(t_connect *head, t_connect *tail,
				t_room *start, t_room *end)
{
	t_connect	*connect;
	t_way		*ways;
	t_way		*ways_begin;

	ways = NULL;
	ways_begin = NULL;
	while (head)
	{
		connect = (head->room->in_part) ?
				head->room->in_part->connects : head->room->connects;
		while (connect && connect->weight != -1)
			connect = connect->next;
		if (connect && connect->weight == -1)
		{
			tail->turn_next = connect;
			connect->parrent = head;
			tail = tail->turn_next;
		}
		if (head->room == start)
			ways = ft_add_path(head, ways, end);
		if (!ways_begin && ways)
			ways_begin = ways;
		head = head->turn_next;
	}
	return (ways_begin);
}
