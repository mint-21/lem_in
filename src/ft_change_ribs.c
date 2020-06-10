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

static void	ft_redirection_link(t_room *src, t_room *dst, t_link *link)
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

/*
** ft_find_null: находим комнаты для обратных ребер и удаляем их связи
** ft_redirection_link: перенаправление связей в структуре two
*/

void		ft_change_ribs(t_path *path)
{
	while (path && path->next)
	{
		t_link	*link;

		ft_find_null(path);
		link = path->room->links;
		while (link && link->room != path->next->room)
			link = link->next;
		if (link && link->room == path->next->room)
			ft_redirection_link(path->room, path->next->room, link);
		path = path->next;
	}
}
