/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:16:04 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/17 14:22:57 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Finding the shortest paths in a graph with incoming and outgoing nodes
** Create Inbound Nodes
** ++(*weight): path weight
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

int	check_empty(t_way *way)
{
	while (way)
	{
		if (way->ants)
			return (1);
		way = way->next;
	}
	return (0);
}

/*
** We initialize the structure of paths way
*/

void	ft_perror(void)
{
	perror("lem-in");
	exit(1);
}
