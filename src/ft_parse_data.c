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
** ft_links: основная функция связи между комнатами
** ft_free_str_split: очистка двумерного массива после занесения всех данных
*/

int	ft_parse_data(t_data *data, char **strings)
{
	int	i;

	i = data->i_rooms_start - 1;
	while (++i <= data->i_rooms_end)
	{
		if (strings[i][0] != '#')
			ft_rooms(data, strings[i]);
		if (i == data->i_start)
			data->start = data->rooms;
		else if (i == data->i_end)
			data->end = data->rooms;
	}
	i = data->i_links_start - 1;
	while (++i <= data->i_links_end)
		if (strings[i][0] != '#')
			ft_links(data, strings[i]);
	ft_free_str_split(strings);
	return (0);
}
