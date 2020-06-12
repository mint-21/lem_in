/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_ribs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:58:22 by asmall            #+#    #+#             */
/*   Updated: 2020/04/27 20:57:48 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** ft_find_null: находим комнаты для обратных ребер и удаляем их связи
** ft_redirection_connect: перенаправление связей в структуре two
*/

void		ft_change_ribs(t_path *path)
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
