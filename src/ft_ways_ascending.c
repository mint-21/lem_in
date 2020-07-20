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
** Находим новые кратчайшие пути в графе с входящими и исходящими узлами
** ++(*weight): вес пути
*/

static t_path	*ft_path(t_connect *head, int *weight, t_room *end)
{
	t_path	*path;
	t_path	*tmp;

	path = NULL;
	while (head)
	{
		tmp = path;
		if (!(path = (t_path *)malloc(sizeof(t_path))))
			ft_perror();
		path->room = (head->room->in_part) ? head->room->in_part : head->room;
		path->next = tmp;
		if (tmp)
			tmp->prev = path;
		++(*weight);
		head = head->parrent;
	}
	tmp = path;
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		ft_perror();
	path->room = end;
	path->next = tmp;
	path->prev = NULL;
	if (tmp)
		tmp->prev = path;
	return (path);
}

/*
** Инициализируем новую структуру путей ways
** ft_path: ноходим кратчайшие пути в новом графе с их весом
*/

static t_way	*ft_add_path(t_connect *head, t_way *ways, t_room *end)
{
	t_path		*path;
	t_way		*way;
	int			weight;

	weight = 0;
	path = ft_path(head, &weight, end);
	if (!(way = (t_way *)malloc(sizeof(t_way))))
		ft_perror();
	way->path = path;
	way->path_cost = weight;
	way->ants = 0;
	if (ways)
		ways->next = way;
	way->prev = ways;
	way->next = NULL;
	way->path_number = (ways) ? ways->path_number + 1 : 1;
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
