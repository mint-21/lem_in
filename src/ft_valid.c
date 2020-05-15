/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <ddarell@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:06:00 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/12 13:40:22 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	valid_strings(t_data *data, char *str, int i)
{
	if (str[0] == '\0' || str[0] == 'L')
		ft_print_error(E_NO_VALID);
	else if (!(data->ants))
		ft_valid_ants(str, data);
	else if (str[0] == '#')
		ft_valid_hash(data, str);
	else if (str[0] != '#' && ft_strchr(str, ' '))
		ft_valid_rooms(str, data, i);
	else if (str[0] != '#' && ft_strchr(str, '-'))
		ft_valid_links(str, data, i);
	else
		ft_print_error(E_NO_VALID);
}

/*
** valid_strings: валидация муравьев, комнат, связей.
** ft_valid_duplicates_rooms: проверка на дубликаты комнат.
*/

int			ft_valid(t_data *data, char **strings)
{
	int	i;

	i = -1;
	while (strings[++i])
		valid_strings(data, strings[i], i);
	if (data->v_flag != 29)
		ft_print_error(E_NO_VALID);
	ft_valid_duplicates_rooms(data, strings);
	return (0);
}
