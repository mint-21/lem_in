/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialization_struct_room.c                    :+:      :+:    :+:   */
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

t_room			*ft_initialization_struct_room(char *name)
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

/*
** The connection is checked up to the '-' sign with the name of the room.
** r_connect[i]: the name of the room before the '-' sign.
** The connection after the '-' sign with the name of the room is checked.
** r_connect[j]: the name of the room after the '-' sign.
*/

int				ft_find_link_name(char *r_name, char *r_connect, int flag)
{
	int			i;
	int			j;

	i = -1;
	if (flag == 1)
	{
		while (r_name[++i] && r_connect[i] && r_connect[i] != '-')
			if (r_name[i] != r_connect[i])
				return (0);
		if (r_name[i] == '\0' && r_connect[i] == '-')
			return (1);
	}
	else if (flag == 2)
	{
		j = 0;
		while (r_connect[j] && r_connect[j] != '-')
			++j;
		while (r_name[++i] & r_connect[++j])
			if (r_name[i] != r_connect[j])
				return (0);
		if (r_name[i] == '\0' && r_connect[j] == '\0')
			return (1);
	}
	return (0);
}

/*
** Search for room connections.
** head: the first room in the t_room structure.
*/

int				ft_check_room_link(t_data *data, char *connect_str,
					t_room **room1, t_room **room2)
{
	t_room		*head;

	(!room1 || !room2) ? ft_perror() : 0;
	head = data->rooms;
	while (head && (!(*room1) || !(*room2)))
	{
		if (!(*room1) && ft_find_link_name(head->name, &connect_str[0], 1))
			*room1 = head;
		else if (!(*room2) && ft_find_link_name(head->name, connect_str, 2))
			*room2 = head;
		head = head->next;
	}
	(!(*room1) || !(*room2)) ? ft_print_error(E_NO_CORRECT) : 0;
	return (0);
}
