/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 13:19:23 by vfearles          #+#    #+#             */
/*   Updated: 2020/10/09 13:19:27 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			terms_null(t_room *room)
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
** The function counts the number of ants on each path
** ++way->ants: counting the number of ants passing through the path
*/

void			terms_staps(t_way *way, t_data *data, int steps, t_buf *buf)
{
	t_path		*path;

	path = way->path;
	while (path)
	{
		if (path->room == data->start && data->start->ant &&
			(way->path_cost <= steps || way->path_number == 1))
		{
			copy_text_buff(data, path, buf, ++data->ant);
			++way->ants;
		}
		else if (path->room != data->start && path->room != data->end
			&& path->room->ant)
			copy_text_buff(data, path, buf, path->room->ant);
		path = path->next;
	}
}

/*
** conditions for the implementation of incoming nodes
*/

t_connect		*terms(t_connect *head, t_connect *connect)
{
	if (head->room->in_part)
		connect = head->room->in_part->connects;
	else
		connect = head->room->connects;
	while (connect && connect->weight != -1)
		connect = connect->next;
	return (connect);
}
