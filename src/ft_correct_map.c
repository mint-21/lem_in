/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:39 by asmall            #+#    #+#             */
/*   Updated: 2020/04/27 21:06:50 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_data	ft_zerodata(void)
{
	t_data data;

	data.ants = 0;
	data.rooms_count = 0;
	data.total_ways = 0;
	data.start = NULL;
	data.end = NULL;
	data.rooms = NULL;
	data.options = NULL;
	data.best_opt = NULL;
	data.ways_dij = NULL;
	data.flags.fd_path = NULL;
	data.flags.ways = 0;
	data.check.valid_flag = 0;
	data.check.li_room_begin = 0;
	data.check.li_room_finish = 0;
	data.check.li_connects_bigin = 0;
	data.check.li_connects_finish = 0;
	data.check.hash_start = 0;
	data.check.hash_end = 0;
	return(data);
}

/*
** ft_correct_ants: checks the value of ants with atoi
** puts the number of ants in the struct, sets the flag
*/

int				ft_correct_ants(char *str, t_data *data)
{
	long int	res;
	int			negative;

	negative = 1;
	res = 0;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	if (*str || !((res *= negative) >= 0 && res <= INT_MAX))
		ft_print_error(E_INT);
	data->ants = ((int)res);
	data->check.valid_flag = E_ANT;
	return (0);
}

/*
** ft_correct_rooms: write room-start/room-end in struct
** checking coordinates for int, the presence of two spaces
*/

int				ft_correct_rooms(char *str, t_valid *check, int j)
{
	int			space;

	space = 0;
	while (*str && *str != '-' && *str != ' ')
		str++;
	while (*str && !(*str == '\r'))
	{
		if (*str != ' ')
			ft_print_error(E_ROOM);
		space++;
		str = (*str == '+' || *str == '-') ? str + 2 : str + 1;
		while (*str >= '0' && *str <= '9')
			str++;
	}
	(space != 2) ? ft_print_error(E_ROOM) : 1;
	check->li_room_finish = j;
	if (!check->li_room_begin)
		check->li_room_begin = j;
	(check->hash_start == -1) ? check->hash_start = j : 1;
	(check->hash_end == -1) ? (check->hash_end = j) : 1;
	return (0);
}

/*
** ft_correct_rooms_double: check rooms for doublicate x and y
*/

int		check_double_coor(t_data *s, t_room *curr, char *str)
{
	t_room	*check;
	
	str += ft_strlen(curr->name);
	curr->x = ft_atoi(str);
	str += 1;
	while(*str && *str >= 0 && *str <= 9)
		(*str) += 1;
	curr->y = ft_atoi(str);
	check = s->rooms;
	while (check)
	{
		if (curr->name != check->name && curr->x == check->x 
			&& curr->y == check->y)
			return (1);
		check = check->next;
	}
	return (0);
}

/*
** ft_correct_hash: sets start/end flag, skip comments/command
*/

int				ft_correct_hash(t_valid *check, char *str)
{
	if (ft_strequ(str, "##start"))
	{
		if (check->hash_start || check->hash_end == -1)
			ft_print_error(E_START);
		check->hash_start = -1;
		check->valid_flag += E_START;
	}
	else if (ft_strequ(str, "##end"))
	{
		if (check->hash_end || check->hash_start == -1)
			ft_print_error(E_END);
		check->hash_end = -1;
		check->valid_flag += E_END;
	}
	else if (*str == '#' && (check->hash_start == -1 
		|| check->hash_end == -1))
		ft_print_error(E_HASH);
	return (0);
}

/*
** ft_correct_connects: check '-', write connect-start/end in struct
*/

void			ft_correct_connects(char *str, t_valid *check, int j)
{
	if (check->valid_flag == 12 && check->hash_start != -1
		&& check->hash_end != -1)
		check->valid_flag += E_ROOM;
	if (ft_strchr(str, ' ') || !ft_strchr(str, '-'))
		ft_print_error(E_CONNECT);
	if (!check->li_connects_bigin)
	{
		check->li_connects_bigin = j;
		check->valid_flag += E_CONNECT;
	}
	check->li_connects_finish = j;
}
