/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_lemin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:58:17 by vfearles          #+#    #+#             */
/*   Updated: 2020/05/13 19:33:59 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	check_room(char *str)
{
	int		space;

	space = 0;
	while (*str && *str != '-' && *str != ' ')
		str++;
	while (*str && !(*str == '\r'))
	{
		if (*str == ' ')
		{
			str++;
			space++;
		}
		else
			ft_print_error(E_ROOM);
		str = (*str == '+' || *str == '-') ? str + 1 : str;
		(*str >= '0' && *str <= '9') ? 1 : ft_print_error(E_ROOM);
		while (*str >= '0' && *str <= '9')
			str++;
	}
	(space != 2) ? ft_print_error(E_ROOM) : 1;
}

int			ft_valid_rooms(char *str, t_data *data, int j)
{
	check_room(str);
	data->i_rooms_end = j;
	if (!data->i_rooms_start)
		data->i_rooms_start = j;
	if (data->i_start == -1)
		data->i_start = j;
	if (data->i_end == -1)
		data->i_end = j;
	return (0);
}
