/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srb_alg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:39:25 by vfearles          #+#    #+#             */
/*   Updated: 2020/10/08 18:39:28 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Set room_par to zero and weight to timestamp
*/

static void		null(t_room *room)
{
	while (room)
	{
		if (room->state)
		{
			room->room_par = NULL;
			room->weight = INF;
			terms_null(room);
		}
		room = room->next;
	}
}

/*
** Duplicate all intermediate vertices of the found path
*/

static void		identical_rooms(t_path *path)
{
	t_room		*in;

	while (path)
	{
		if (!path->next || !path->next->next)
			return ;
		in = path->next->room;
		ft_creat_duplicate(path, in);
		path = path->next;
	}
}

/*
** ft_find_null: find rooms for back edges and remove their connections
** ft_redirection_connect: redirecting links in structure
*/

void			ft_change_ribs(t_path *path)
{
	t_connect	*connect;

	while (path && path->next)
	{
		ft_find_null(path);
		connect = path->room->connects;
		while (connect && connect->room != path->next->room)
			connect = connect->next;
		if (connect && connect->room == path->next->room)
		{
			redirection_conditions(connect, path->room);
			ft_redirection_connect(path->room, path->next->room, connect);
		}
		path = path->next;
	}
}

/*
** path: creating the n-part of the path, initializing the t_way
** and t_path structures.
** null: we return the structure to its original state weight.
*/

static int		ft_dij_path(t_data *data, int flag)
{
	data->start->weight = 0;
	djkastra(flag, data, data->rooms_count);
	if (!data->end->room_par)
		return (0);
	path(data->end, data->start, &data->ways_dij, 0);
	null(data->rooms);
	return (1);
}

/*
** ft_dij_path: Dijkstra Breadth First Search
** ft_change_ribs: make the graph directional and change the direction
** of the edges
** identical_rooms: duplicate all intermediate vertices of the path part
*/

int				ft_srb_alg(t_data *data)
{
	int flag;

	flag = 1;
	if (ft_dij_path(data, flag))
	{
		ft_change_ribs(data->ways_dij->path);
		identical_rooms(data->ways_dij->path);
		return (1);
	}
	return (0);
}
