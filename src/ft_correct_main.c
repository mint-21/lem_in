/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <ddarell@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:06:00 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/12 13:40:22 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** ft_rooms: main funct to init and write info about rooms
** ft_connects: основная функция связи между комнатами
** ft_free_str_split: очистка двумерного массива после занесения всех данных
*/

int				ft_init_room(t_data *data, t_valid *check, char **str)
{
	int	i;
	t_room		*room;

	i = check->li_room_begin - 1;
	while (++i <= check->li_room_finish)
	{
		if (str[i][0] != '#')
		{
			room = ft_createroom(str[i]);
			if (check_double_coor(data, room, str[i]))
				ft_print_error(E_NO_CORRECT);
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

static void	correct_strings(t_data *data, t_valid *check, char *str, int i)
{
	if (str[0] == '\0' || str[0] == 'L')
		ft_print_error(E_NO_CORRECT);
	else if (!(data->ants))
		ft_correct_ants(str, data);
	else if (str[0] == '#')
		ft_correct_hash(check, str);
	else if (str[0] != '#' && ft_strchr(str, ' '))
		ft_correct_rooms(str, check, i);
	else if (str[0] != '#' && ft_strchr(str, '-'))
		ft_correct_connects(str, check, i);
	else
		ft_print_error(E_NO_CORRECT);
}

/*
** correct_strings: валидация муравьев, комнат, связей.
** ft_correct_rooms_duble: проверка на дубликаты комнат.
*/

int			ft_correct(t_data *data, t_valid *check, char **strings)
{
	int	i;

	i = -1;
	while (strings[++i])
		correct_strings(data, check, strings[i], i);
	if (check->valid_flag != 29)
		ft_print_error(E_NO_CORRECT);
	ft_init_room(data, check, strings);
	return (0);
}
