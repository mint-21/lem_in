/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:06:00 by asmall            #+#    #+#             */
/*   Updated: 2020/06/12 13:40:22 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_zerodata2(t_data *data)
{
	data->map_data = NULL;
	data->split = NULL;
	data->start = NULL;
	data->end = NULL;
	data->rooms = NULL;
	data->options = NULL;
	data->best_opt = NULL;
	data->ways_dij = NULL;
	data->flags.fd_path = NULL;
}

t_data		ft_zerodata(void)
{
	t_data	data;

	data.ants = 0;
	data.step = 0;
	data.flag = 1;
	data.rooms_count = 0;
	data.total_ways = 0;
	data.links_count = 0;
	ft_zerodata2(&data);
	data.flags.ways = 0;
	data.check.valid_flag = 0;
	data.check.li_room_begin = 0;
	data.check.li_room_finish = 0;
	data.check.li_connects_bigin = 0;
	data.check.li_connects_finish = 0;
	data.check.hash_start = 0;
	data.check.hash_end = 0;
	data.links = NULL;
	data.vis_quit = 0;
	data.vis_pause = 0;
	return (data);
}

/*
** ft_create: main funct to init and write info about rooms
** ft_connects: основная функция связи между комнатами
** ft_split_free: очистка двумерного массива после занесения всех данных
*/

static void		free_init(int i, t_valid *check, t_data *data, char **str)
{
	while (++i <= check->li_connects_finish)
	{
		(str[i][0] != '#') ? ft_connects(data, str[i]) : 0;
		add_link(data, str[i]);
	}
	ft_split_free(str);
}

int				ft_init_room(t_data *data, t_valid *check, char **str)
{
	int			i;
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
			room->n = room->next == NULL ? 0 : room->next->n + 1;
		}
		data->start = (i == check->hash_start) ? data->rooms : data->start;
		data->end = (i == check->hash_end) ? data->rooms : data->end;
	}
	i = check->li_connects_bigin - 1;
	free_init(i, check, data, str);
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
	while (strings[++i] && strings[i][0] != 'L')
		correct_strings(data, check, strings[i], i);
	if (check->valid_flag != 29)
		ft_print_error(E_NO_CORRECT);
	ft_init_room(data, check, strings);
	return (0);
}
