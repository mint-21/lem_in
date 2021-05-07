/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:50:26 by asmall            #+#    #+#             */
/*   Updated: 2021/04/21 14:53:33 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_way	*plist_push_back(t_way *way, t_path *p, int len)
{
	t_way	*first;
	t_way	*new;
	t_path	*w;

	w = p;
	first = way;
	new = (t_way *)ft_memalloc(sizeof(t_way));
	if (!new)
		exit(1);
	while (w)
	{
		w = w->next;
		len++;
	}
	new->len = len;
	new->path = p;
	if (!first)
		return (new);
	while (way->next)
		way = way->next;
	way->next = new;
	new->prev = way;
	return (first);
}

void	suurb(t_data *data)
{
	t_way	*way;
	t_room	*rooms;
	int		len;
	t_rooms	*buf;

	len = 0;
	rooms = data->rooms;
	buf = NULL;
	while (rooms)
	{
		rooms->weight = INF;
		rooms = rooms->next;
	}
	data->start->weight = 0;
	way = NULL;
	way = max_path(data, way, len, buf);
	merge(way, buf);
	free_list(way);
	if (data->ways)
		bubble_sort(data->ways, data->ways);
}
