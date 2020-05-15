/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
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
** Удаление предыдущих связей в следующей связующей комнате,
** чтобы граф не был двунаправленным.
*/

static void	ft_delete_link(t_room *dst, t_room *src)
{
	t_link	*link;

	link = dst->links;
	while (link && link->room != src)
		link = link->next;
	if (link && link->room == src)
	{
		if (link->prev)
			link->prev->next = link->next;
		else
			dst->links = link->next;
		if (link->next)
			link->next->prev = link->prev;
		free(link);
	}
}

/*
** room_one: комната со связями; room_two: следующая связующая комната.
** ft_delete_link: удаление предыдущих связей
** ft_redirection_link: перенаправление связей в структуре two
*/

void		ft_direction(t_path *path)
{
	t_room	*room_one;
	t_room	*room_two;

	while (path && path->next)
	{
		room_one = path->room;
		room_two = path->next->room;
		if (!(room_one->room_in || room_one->room_out) &&
		!(room_two->room_in || room_two->room_out))
			ft_delete_link(room_two, room_one);
		else if (!(room_one->room_in || room_one->room_out) &&
		room_two->room_out)
			ft_delete_link(room_two->room_out, room_one);
		else if (!(room_one->room_in || room_one->room_out) &&
		room_two->room_in)
			ft_delete_link(room_two->room_in, room_one);
		else if (room_one->room_in &&
		!(room_two->room_in || room_two->room_out))
			ft_delete_link(room_two, room_one->room_in);
		else if (room_one->room_out &&
		!(room_two->room_in || room_two->room_out))
			ft_delete_link(room_two, room_one->room_out);
		ft_redirection_link(room_one, room_two);
		path = path->next;
	}
}
