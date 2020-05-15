/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:17:51 by vfearles          #+#    #+#             */
/*   Updated: 2019/10/16 17:17:52 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Инициализация структуры связей
*/

t_link		*ft_createlink(t_room *room)
{
	t_link	*link;

	if (!(link = (t_link *)malloc(sizeof(t_link))))
		ft_perror();
	link->weight = 1;
	link->room_one = NULL;
	link->room = room;
	link->next = NULL;
	link->prev = NULL;
	link->turn_next = NULL;
	link->parrent = NULL;
	return (link);
}

/*
** Создание связей в структуре и инициализация.
*/

static void	ft_connectlink(t_room *room_one, t_room *room_two)
{
	t_link	*link;
	t_link	*tmp;

	link = ft_createlink(room_two);
	if (room_one->links)
	{
		tmp = room_one->links;
		room_one->links = link;
		link->next = tmp;
		tmp->prev = link;
	}
	else
		room_one->links = link;
	link->room_one = room_one;
	room_one->links_count += 1;
}

/*
** Проверка на повторяющиеся связи>
*/

static int	ft_check_duplicate_link(t_room *room1, t_room *room2)
{
	t_link	*link;

	link = room1->links;
	while (link)
	{
		if (link->room == room2)
			return (1);
		link = link->next;
	}
	return (0);
}

/*
** ft_findrooms: поиск связующих комнат.
** ft_check_duplicate_link: проверка на повторяющиеся связи.
** ft_connectlink: связываем комнаты друг с другом в структуре.
*/

void		ft_links(t_data *data, char *link_str)
{
	t_room	*room1;
	t_room	*room2;

	room1 = NULL;
	room2 = NULL;
	ft_findrooms(data, link_str, &room1, &room2);
	if (!ft_check_duplicate_link(room1, room2))
	{
		ft_connectlink(room1, room2);
		ft_connectlink(room2, room1);
	}
}
