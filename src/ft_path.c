/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:43:22 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 14:53:33 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path	*p_push_begin(t_room *r, t_path *p)
{
	t_path	*new;

	new = (t_path *)ft_memalloc(sizeof(t_path));
	if (!new)
		exit(1);
	new->room = r;
	new->next = p;
	if (p)
		p->prev = new;
	return (new);
}

int	p_len(t_path *p)
{
	int	len;

	len = 0;
	while (p)
	{
		p = p->next;
		len++;
	}
	return (len);
}

void	recount_len(t_way *l)
{
	while (l)
	{
		l->len = p_len(l->path);
		l = l->next;
	}
}

t_way	*add_data(t_path *p, t_data *data, t_way *way)
{
	while (p->next)
	{
		p->room->connects = del_link(p->room->connects, p->next->room);
		p = p->next;
	}
	data->ways = check_steps(way, data->ways, data->ants);
	restore(data, way);
	return (way);
}

t_way	*max_path(t_data *data, t_way *way, int len, t_rooms *buf)
{
	int		max_path;
	t_path	*p;

	max_path = get_max_path(data->start, data->end);
	while (max_path > 0)
	{
		 --max_path;
		split(way);
		p = bfs(data, len);
		if (!p)
			break ;
		way = plist_push_back(way, p, len);
		merge(way, buf);
		if (collision_handle(way, p->next, 0))
			recount_len(way);
		way = add_data(p, data, way);
		max_path = get_max_path(data->start, data->end);
	}
	return (way);
}
