/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:39 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 14:45:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** ft_correct_ants: checks the value of ants with atoi
** puts the number of ants in the struct, sets the flag
*/

int	ft_correct_ants(char *str, t_data *data)
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
	res *= negative;
	if (*str || !(res >= 0 && res <= INT_MAX))
		ft_print_error(E_ANT);
	data->ants = ((int)res);
	data->check.valid_flag = E_ANT;
	return (0);
}

/*
** ft_correct_rooms: write room-start/room-end in struct
** checking coordinates for int, the presence of two spaces
*/

void	ft_rooms_check(t_valid *check, int j)
{
	if (!check->li_room_begin)
		check->li_room_begin = j;
	if (check->hash_start == -1)
		check->hash_start = j;
	if (check->hash_end == -1)
		check->hash_end = j;
}

int	ft_correct_rooms(char *str, t_valid *check, int j)
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
		if (*str == '+' || *str == '-')
			str = str + 2;
		else
			str = str + 1;
		if (!*str && space == 2)
			ft_print_error(E_ROOM);
		while (*str >= '0' && *str <= '9')
			str++;
	}
	if (space != 2)
		ft_print_error(E_ROOM);
	check->li_room_finish = j;
	ft_rooms_check(check, j);
	return (0);
}

/*
** ft_correct_hash: sets start/end flag, skip comments/command
*/

int	ft_correct_hash(t_valid *check, char *str)
{
	if (ft_strequ(str, "##start"))
	{
		if (check->hash_start || check->hash_end == -1)
			ft_print_error(E_END);
		check->hash_start = -1;
		check->valid_flag += E_START;
	}
	else if (ft_strequ(str, "##end"))
	{
		if (check->hash_end || check->hash_start == -1)
			ft_print_error(E_START);
		check->hash_end = -1;
		check->valid_flag += E_END;
	}
	else if (*str == '#' && (check->hash_start == -1 || check->hash_end == -1))
		ft_print_error(E_HASH);
	return (0);
}

/*
** ft_correct_connects: check '-', write connect-start/end in struct
*/

void	ft_correct_connects(char *str, t_valid *check, int j)
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
