/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_createroom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:04:05 by asmall            #+#    #+#             */
/*   Updated: 2020/06/13 20:04:06 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** room structure
*/

t_room			*ft_createroom(char *name)
{
	t_room		*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		ft_perror();
	if (!(room->name = ft_strsub(name, 0, ft_strlen_char(name, " "))))
		ft_perror();
	room->connects = NULL;
	room->out_part = NULL;
	room->in_part = NULL;
	room->room_par = NULL;
	room->next = NULL;
	room->ant = 0;
	room->weight = INF;
	room->state = 1;
	return (room);
}

/*
** The function creates outgoing nodes
** We set the weight of edges from outgoing to incoming nodes to 0,
** vice versa -1
*/

void			create_out_room(t_room *in, t_room *out, t_room *room,
					t_connect *connect)
{
	while (connect && connect->room != room)
		connect = connect->next;
	if (connect && connect->room == room)
	{
		connect->room = in;
		connect->room_one = out;
		connect->weight = 0;
	}
	else
		in->connects = connect;
}

void			create_out_in_room(t_room *in, t_room *out)
{
	t_connect	*connect;

	connect = in->connects;
	while (connect && connect->room != out)
		connect = connect->next;
	if (connect && connect->room == out)
		connect->room = out->out_part;
}
