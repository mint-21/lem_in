/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_ribs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:58:22 by asmall            #+#    #+#             */
/*   Updated: 2020/04/27 20:57:48 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Заменяем ребра из найденного кратчайшего пути обратными ребрами с отриц весом
*/

#include "lemin.h"

static void	ft_redirection_link(t_room *src, t_room *dst)
{
	t_link	*link;

	link = src->links;
	while (link && link->room != dst)
		link = link->next;
	if (link && link->room == dst)
	{
		if (link->prev)
			link->prev->next = link->next;
		else
			src->links = link->next;
		if (link->next)
			link->next->prev = link->prev;
		link->weight = (link->weight == -1) ? 2 : -1;
		link->room = src;
		link->room_one = dst;
		link->prev = NULL;
		link->next = dst->links;
		if (dst->links)
			dst->links->prev = link;
		dst->links = link;
	}
}

/*
** path->room: комната со связями; path->next->room: следующая связующая комната.
** ft_null_link: удаление предыдущих связей
** ft_redirection_link: перенаправление связей в структуре two
*/

void		ft_change_ribs(t_path *path)
{
	while (path && path->next)
	{
		if (!(path->room->in_part || path->room->out_part))
		{
			if (!(path->next->room->in_part || path->next->room->out_part))
				ft_null_link(path->next->room, path->room);
			else if (path->next->room->out_part)
				ft_null_link(path->next->room->out_part, path->room);
			else if (path->next->room->in_part)
				ft_null_link(path->next->room->in_part, path->room);
		}
		else if (!(path->next->room->in_part || path->next->room->out_part))
		{
			if (path->room->in_part)
				ft_null_link(path->next->room, path->room->in_part);
			else if (path->room->out_part)
				ft_null_link(path->next->room, path->room->out_part);
		}
		ft_redirection_link(path->room, path->next->room);
		path = path->next;
	}
}
