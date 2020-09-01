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
** Находим кратчайшие пути в графе с входящими и исходящими узлами
** Создаем входящие узлы
** ++(*weight): вес пути
*/

t_connect	*create_inhead(t_path *tmp, t_path *path, t_connect *head,
					int *weight)
{
	if (head->room->in_part)
		path->room = head->room->in_part;
	else
		path->room = head->room;
	path->next = tmp;
	if (tmp)
		tmp->prev = path;
	++(*weight);
	head = head->parrent;
	return (head);
}

/*
** Инициализируем структуру путей way
*/

t_way		*way_init(t_way *way, t_path *path, int weight, t_way *ways)
{
	way->path = path;
	way->path_cost = weight;
	way->ants = 0;
	if (ways)
		ways->next = way;
	way->prev = ways;
	way->next = NULL;
	if (ways)
		way->path_number = ways->path_number + 1;
	else
		way->path_number = 1;
	return (way);
}
