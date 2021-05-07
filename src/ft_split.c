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

void	add_link2(t_connect **l, t_room *dst, int weight)
{
	t_connect	*new;

	new = (t_connect *)ft_memalloc(sizeof(t_connect));
	if (!new)
		exit(1);
	new->next = *l;
	*l = new;
	new->room = dst;
	new->weight = weight;
}

void	split(t_way *way)
{
	t_path	*p;
	t_room	*out;

	while (way)
	{
		p = way->path->next;
		while (p->next)
		{
			out = (t_room *)ft_memalloc(sizeof(t_room));
			if (!out)
				exit(1);
			out->weight = INF;
			out->connects = p->room->connects;
			p->room->connects = NULL;
			add_link2(&out->connects, p->room, 0);
			if (p->prev->room->out_part == NULL)
				add_link2(&p->room->connects, p->prev->room, -1);
			else
				add_link2(&p->room->connects, p->prev->room->out_part, -1);
			p->room->out_part = out;
			out->in_part = p->room;
			p = p->next;
		}
		way = way->next;
	}
}
