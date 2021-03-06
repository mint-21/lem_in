/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:06:00 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 14:42:36 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** ft_create: main funct to init and write info about rooms
** ft_connects: communication function between rooms
** ft_split_free: clearing a two-dimensional array after entering all the data
*/

static void	free_init(int i, t_valid *check, t_data *data, char **str)
{
	while (++i <= check->li_connects_finish)
	{
		if (str[i][0] != '#')
			ft_connects(data, str[i]);
		add_link(data, str[i]);
	}
	ft_split_free(str);
}

void	init_room_process(int i, t_data *data, t_valid *check)
{
	if (i == check->hash_start)
		data->start = data->rooms;
	if (i == check->hash_end)
		data->end = data->rooms;
}

int	ft_init_room(t_data *data, t_valid *check, char **str)
{
	int			i;
	t_room		*room;

	i = check->li_room_begin - 1;
	while (++i <= check->li_room_finish)
	{
		if (str[i][0] != '#')
		{
			room = ft_initialization_struct_room(str[i]);
			if (check_double_coor(data, room, str[i]))
				ft_print_error(E_COORD);
			room->next = data->rooms;
			data->rooms = room;
			data->rooms_count++;
			if (room->next == NULL)
				room->n = 0;
			else
				room->n = room->next->n + 1;
		}
		init_room_process(i, data, check);
	}
	i = check->li_connects_bigin - 1;
	free_init(i, check, data, str);
	return (1);
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
** correct_strings: validation of ants, rooms, connections.
*/

int	ft_correct(t_data *data, t_valid *check, char **strings)
{
	int			i;

	i = -1;
	while (strings[++i] && strings[i][0] != 'L')
		correct_strings(data, check, strings[i], i);
	if (check->valid_flag != 27)
	{
		if (!check->hash_end)
			ft_print_error(E_END);
		else if (!check->hash_start)
			ft_print_error(E_START);
		else
			ft_print_error(E_NO_CORRECT);
	}
	ft_init_room(data, check, strings);
	return (0);
}
