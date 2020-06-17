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
	data->v_flag = E_ANT;
	return (0);
}

/*
** ft_correct_rooms: write room-start/room-end in struct
** checking coordinates for int, the presence of two spaces
*/

int				ft_correct_rooms(char *str, t_data *data, int j)
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
	data->i_rooms_end = j;
	if (!data->i_rooms_start)
		data->i_rooms_start = j;
	(data->i_start == -1) ? data->i_start = j : 1;
	(data->i_end == -1) ? (data->i_end = j) : 1;
	return (0);
}

/*
** ft_correct_rooms_double: check rooms for doublicate
*/

int				ft_correct_rooms_double(char *room1, char *room2)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (room1[i] != ' ' || room2[j] != ' ')
	{
		(room1[i] == ' ') ? i : i++;
		(room2[j] == ' ') ? j : j++;
	}
	if (i == j && !ft_strncmp(room1, room2, (i < j) ? j : i))
		return (1);
	while (room1[++i] && room2[++j])
		if (room1[i] != room2[j])
			return (0);
	return (1);
}

/*
** ft_correct_hash: sets start/end flag, skip comments/command
*/

int				ft_correct_hash(t_data *data, char *str)
{
	if (ft_strequ(str, "##start"))
	{
		if (data->i_start || data->i_end == -1)
			ft_print_error(E_START);
		data->i_start = -1;
		data->v_flag += E_START;
	}
	else if (ft_strequ(str, "##end"))
	{
		if (data->i_end || data->i_start == -1)
			ft_print_error(E_END);
		data->i_end = -1;
		data->v_flag += E_END;
	}
	else if (*str == '#' && (data->i_start == -1 || data->i_end == -1))
		ft_print_error(E_HASH);
	return (0);
}

/*
** ft_correct_connects: check '-', write connect-start/end in struct
*/

void			ft_correct_connects(char *str, t_data *data, int j)
{
	if (data->v_flag == 12 && data->i_start != -1 && data->i_end != -1)
		data->v_flag += E_ROOM;
	if (ft_strchr(str, ' ') || !ft_strchr(str, '-'))
		ft_print_error(E_connect);
	if (!data->i_connects_start)
	{
		data->i_connects_start = j;
		data->v_flag += E_connect;
	}
	data->i_connects_end = j;
}
