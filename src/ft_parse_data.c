/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:04:19 by vfearles          #+#    #+#             */
/*   Updated: 2019/10/13 18:04:22 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** ft_rooms: основная функция инициализации и записи координат комнат
** ft_connects: основная функция связи между комнатами
** ft_free_str_split: очистка двумерного массива после занесения всех данных
*/

int	ft_parse_data(t_data *data, t_valid *check, char **str)
{
	int	i;
	t_room		*room;

	i = check->li_room_begin - 1;
	while (++i <= check->li_room_finish)
	{
		if (str[i][0] != '#')
		{
			room = ft_createroom(str[i]);
			room->next = data->rooms;
			data->rooms = room;
			data->rooms_count++;
		}
		data->start = (i == check->hash_start) ? data->rooms : data->start;
		data->end = (i == check->hash_end) ? data->rooms : data->end;
	}
	i = check->li_connects_bigin - 1;
	while (++i <= check->li_connects_finish)
		(str[i][0] != '#') ? ft_connects(data, str[i]) : 0;
	ft_free_str_split(str);
	return (0);
}
