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
** ft_correct_rooms_double: check rooms for doublicate x and y
*/

int	check_double_coor(t_data *s, t_room *curr, char *str)
{
	t_room		*check;

	str += ft_strlen(curr->name);
	curr->x = ft_atoi(str);
	str += 1;
	while (*str && (*str >= '0' && *str <= '9'))
		str += 1;
	curr->y = ft_atoi(str);
	check = s->rooms;
	while (check)
	{
		if ((!ft_strcmp(curr->name, check->name))
			|| (curr->x == check->x && curr->y == check->y))
			return (1);
		check = check->next;
	}
	return (0);
}
