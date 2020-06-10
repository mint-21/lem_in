/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_farm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 20:04:05 by vfearles          #+#    #+#             */
/*   Updated: 2019/10/13 20:04:06 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Создаем новую структуру для комнаты
*/

t_room			*ft_createroom(char *name)
{
	int			i;
	t_room		*room;

	if (!(room = (t_room *)malloc(sizeof(t_room))))
		ft_perror();
	i = 0;
	while (name[i] != '\0' && name[i] != ' ')
		++i;
	if (!(room->name = ft_strsub(name, 0, i)))
		ft_perror();
	room->x = 0;
	room->y = 0;
	room->links = NULL;
	room->links_count = 0;
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
** Создаем структуру комнаты с именем и ее координатами
*/

static t_room	*ft_createroom_xy(char *line)
{
	int			i;
	t_room		*room;

	room = ft_createroom(line);
	i = (int)ft_strlen(room->name) + 1;
	line += i;
	room->x = ft_atoi(line);
	line += 1;
	room->y = ft_atoi(line);
	return (room);
}

/*
** Создание новой структуры комнаты
*/

void			ft_rooms(t_data *data, char *str)
{
	t_room		*room;

	room = ft_createroom_xy(str);
	room->next = data->rooms;
	data->rooms = room;
	++data->rooms_count;
}
