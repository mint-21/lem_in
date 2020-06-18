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

int	ft_parse_data(t_data *data, t_valid *check, char **strings)
{
	int	i;

	i = check->li_room_begin - 1;
	while (++i <= check->li_room_finish)
	{
		if (strings[i][0] != '#')
			ft_rooms(data, strings[i]);
		if (i == check->hash_start)
			data->start = data->rooms;
		else if (i == check->hash_end)
			data->end = data->rooms;
	}
	i = check->li_connects_bigin - 1;
	while (++i <= check->li_connects_finish)
		if (strings[i][0] != '#')
			ft_connects(data, strings[i]);
	ft_free_str_split(strings);
	return (0);
}
