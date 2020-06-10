/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_ascending.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:00:00 by vfearles          #+#    #+#             */
/*   Updated: 2019/12/04 17:00:01 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Удаление обратных краев(ребер) вместе с их оригиналами
*/

static void		null(t_link *turn_head, t_link *turn_tail, t_room *end)
{
	turn_head = end->links;
	while (turn_head && turn_head->weight != -1)
		turn_head = turn_head->next;
	while (turn_head)
	{
		turn_tail = turn_head->turn_next;
		turn_head->turn_next = NULL;
		turn_head->parrent = NULL;
		turn_head = turn_tail;
	}
}

static void		ft_link_end(t_link **turn_head, t_link **turn_tail)
{
	t_link	*link;

	link = (*turn_head)->next;
	while (link)
	{
		if (link->weight == -1)
		{
			(*turn_tail)->turn_next = link;
			*turn_tail = (*turn_tail)->turn_next;
		}
		link = link->next;
	}
}

/*
** turn_head, turn_tail: обратные края (ребра).
** ft_ways_ascending: поиск кратчайших путей.
** ft_link_end: связи с комнатой end.
** null: удаление обратных краев (ребер).
*/

t_way			*ft_paths_ascending(t_room *start, t_room *end)
{
	t_link	*turn_head;
	t_link	*turn_tail;
	t_way	*ways_begin;

	turn_head = end->links;
	while (turn_head && turn_head->weight != -1)
		turn_head = turn_head->next;
	if (!turn_head)
		return (NULL);
	turn_tail = turn_head;
	ft_link_end(&turn_head, &turn_tail);
	ways_begin = ft_ways_ascending(turn_head, turn_tail, start, end);
	null(turn_head, turn_tail, end);
	return (ways_begin);
}
