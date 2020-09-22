/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:16:04 by vfearles          #+#    #+#             */
/*   Updated: 2020/09/22 11:16:08 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Находим кратчайшие пути в графе с входящими и исходящими узлами
** Создаем входящие узлы
** ++(*weight): вес пути
*/

t_connect		*create_inhead(t_path *tmp, t_path *path, t_connect *head,
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

t_way			*way_init(t_way *way, t_path *path, int weight, t_way *ways)
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

/*
** дополнительные условия для реализации входящих узлов
*/

t_connect		*terms(t_connect *head, t_connect *connect)
{
	if (head->room->in_part)
		connect = head->room->in_part->connects;
	else
		connect = head->room->connects;
	while (connect && connect->weight != -1)
		connect = connect->next;
	return (connect);
}

void			ft_perror(void)
{
	perror("lem-in");
	exit(1);
}

void			terms_null(t_room *room)
{
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
