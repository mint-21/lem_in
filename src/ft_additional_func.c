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
** Finding the shortest paths in a graph with incoming and outgoing nodes
** Create Inbound Nodes
** ++(*weight): path weight
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
** We initialize the structure of paths way
*/

t_way			*way_init(t_way *way, t_path *path, int weight, t_way *ways)
{
	way->path = path;
	way->len = weight;
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

void			ft_perror(void)
{
	perror("lem-in");
	exit(1);
}
