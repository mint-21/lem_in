/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_connects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:17:51 by asmall            #+#    #+#             */
/*   Updated: 2020/07/16 17:17:52 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Link structure initialization
*/

t_connect		*ft_createconnect(t_room *room)
{
	t_connect	*connect;

	if (!(connect = (t_connect *)malloc(sizeof(t_connect))))
		ft_perror();
	connect->weight = 1;
	connect->room_one = NULL;
	connect->room = room;
	connect->next = NULL;
	connect->prev = NULL;
	connect->turn_next = NULL;
	connect->parrent = NULL;
	return (connect);
}

/*
** Creation of links in the structure and initialization.
*/

static void		ft_connectconnect(t_room *room_one, t_room *room_two)
{
	t_connect	*connect;
	t_connect	*tmp;

	connect = ft_createconnect(room_two);
	if (room_one->connects)
	{
		tmp = room_one->connects;
		room_one->connects = connect;
		connect->next = tmp;
		tmp->prev = connect;
	}
	else
		room_one->connects = connect;
	connect->room_one = room_one;
	room_one->connects_count += 1;
}

static int		ft_check_duplicate_connect(t_room *room1, t_room *room2)
{
	t_connect	*connect;

	connect = room1->connects;
	while (connect)
	{
		if (connect->room == room2)
			return (1);
		connect = connect->next;
	}
	return (0);
}

/*
** ft_findrooms: search for connecting rooms.
** ft_check_duplicate_connect: checking for duplicate connections.
** ft_connectconnect: connect rooms in the structure.
*/

void			ft_connects(t_data *data, char *connect_str)
{
	t_room		*room1;
	t_room		*room2;

	room1 = NULL;
	room2 = NULL;
	ft_findrooms(data, connect_str, &room1, &room2);
	if (!ft_check_duplicate_connect(room1, room2))
	{
		ft_connectconnect(room1, room2);
		ft_connectconnect(room2, room1);
	}
}
