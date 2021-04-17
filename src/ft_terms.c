/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:19:23 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/17 15:02:18 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	terms_null(t_room *room)
{
	if (room->out_part)
	{
		room->out_part->room_par = NULL;
		room->out_part->weight = INF;
	}
	else if (room->in_part)
	{
		room->in_part->room_par = NULL;
		room->in_part->weight = INF;
	}
}

/*
** conditions for the implementation of incoming nodes
*/

t_connect	*terms(t_connect *head, t_connect *connect)
{
	if (head->room->in_part)
		connect = head->room->in_part->connects;
	else
		connect = head->room->connects;
	while (connect && connect->weight != -1)
		connect = connect->next;
	return (connect);
}

void	terms_connect(t_room *room_one, t_connect *connect)
{
	t_connect	*tmp;

	connect->prev = NULL;
	connect->turn_next = NULL;
	connect->parrent = NULL;
	if (room_one->connects)
	{
		tmp = room_one->connects;
		room_one->connects = connect;
		connect->next = tmp;
		tmp->prev = connect;
	}
	else
		room_one->connects = connect;
}
