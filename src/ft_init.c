/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
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

void		init_way(t_way *way, int path_cost, t_way **ways, t_path *path)
{
	way->path = path;
	way->path_number = (*ways) ? (*ways)->path_number + 1 : 1;
	way->path_cost = path_cost;
	way->ants = 0;
	way->prev = NULL;
	way->next = *ways;
}

/*
** Инициализация
*/

void		path_init(t_path *path, t_room *end, t_path *tmp)
{
	path->room = end;
	path->next = tmp;
	path->prev = NULL;
}

int			ft_init_path_struct(t_path *path, t_room *room, int path_cost)
{
	path_cost = room->weight;
	path->room = room;
	path->next = NULL;
	path->prev = NULL;
	return (path_cost);
}