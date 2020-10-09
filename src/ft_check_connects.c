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
** Creation of links in the structure and initialization
*/

static void		ft_connectconnect(t_room *room_one, t_room *room_two)
{
	t_connect	*connect;

	(!(connect = (t_connect *)malloc(sizeof(t_connect)))) ? ft_perror() : 0;
	connect->weight = 1;
	connect->room_one = NULL;
	connect->room = room_two;
	connect->next = NULL;
	terms_connect(room_one, connect);
	connect->room_one = room_one;
	room_one->connects_count += 1;
}

/*
** ft_check_room_link: search for connecting rooms.
** ft_check_duplicate_connect: checking for duplicate connections.
** ft_connectconnect: connect rooms in the structure.
*/

void			ft_connects(t_data *data, char *connect_str)
{
	t_room		*one;
	t_room		*two;
	t_connect	*connect;

	one = NULL;
	two = NULL;
	ft_check_room_link(data, connect_str, &one, &two);
	connect = one->connects;
	while (connect)
	{
		if (connect->room == two)
			return ;
		connect = connect->next;
	}
	ft_connectconnect(one, two);
	ft_connectconnect(two, one);
}
