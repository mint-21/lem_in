/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_duplicate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:27:26 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 14:47:13 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Link structure initialization
*/

t_connect	*ft_createconnect(t_room *room)
{
	t_connect	*connect;

	connect = (t_connect *)malloc(sizeof(t_connect));
	if (!connect)
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
** Duplicate all intermediate vertices of the found path to the incoming
** and outgoing nodes.
** create_out_room: creating outgoing nodes
** end initially points to the incoming portion and is not redirected
*/

void	ft_creat_duplicate(t_path *path, t_room *in)
{
	t_connect	*links;
	t_room		*out;

	if (!in->out_part && !in->in_part)
	{
		out = ft_initialization_struct_room(in->name);
		in->out_part = out;
		out->in_part = in;
		if (path->room->out_part)
			links = ft_createconnect(path->room->out_part);
		else
			links = ft_createconnect(path->room);
		links->weight = -1;
		links->room_one = in;
		out->connects = in->connects;
		in->connects = links;
		links = out->connects;
		create_out_room(in, out, path->room, links);
	}
	else if (in->out_part && !path->room->in_part)
	{
		out = path->room;
		create_out_in_room(in, out);
	}
}
