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
	int j;

	i = -1;
	while (strings[++i])
		correct_strings(data, check, strings[i], i);
	if (check->valid_flag != 29)
		ft_print_error(E_NO_CORRECT);
	i = check->li_room_begin - 1;
	while (++i <= check->li_room_finish)
	{
		if (strings[i][0] == '#')
			break ;
		j = i;
		while (++j <= check->li_room_finish)
		{
			if (strings[j][0] != '#')
				if (ft_correct_rooms_double(strings[i], strings[j]))
					ft_print_error(E_MALLOC);
		}
	}
	return (0);
}
