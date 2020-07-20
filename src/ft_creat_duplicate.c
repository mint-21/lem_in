/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_suurballe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:27:26 by vfearles          #+#    #+#             */
/*   Updated: 2019/11/14 17:27:26 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Дублируем все промежуточные вершины найденного пути на входящие
** и исходящие узлы.
** create_out_room: создание исходящих узлов
** end изначально указывает на входящую часть и не перенаправляется
*/

void    ft_creat_duplicate(t_path *path, t_room *in)
{
	t_connect	*links;
    t_room      *out;

    if (!in->out_part && !in->in_part)
	{
		out = ft_createroom(in->name);
		in->out_part = out;
		out->in_part = in;
		links = ft_createconnect((path->room->out_part) ?
                        path->room->out_part : path->room);
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