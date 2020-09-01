/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_all_ways.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:37:00 by vfearles          #+#    #+#             */
/*   Updated: 2020/05/13 19:31:48 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Считает количество связей с start и количество связей, приходящих в end
** Функция возвращает наименьшее из подсчитанных значений.
*/

static int		find_ways(t_room *start, t_room *end)
{
	int			i;
	int			j;
	t_connect		*ptr;
	t_connect		*src;

	i = -1;
	j = -1;
	ptr = start->connects;
	src = end->connects;
	while (ptr || src)
	{
		++i;
		++j;
		if (ptr)
			ptr = ptr->next;
		else if (src)
			src = src->next;
	}
	return ((j < i) ? j : i);
}

/*
** find_ways: возвращает количество путей
** ft_suurballe: ф-ия создает новый граф с входящими и исходящими узлами
** В главную структуру добавляем структуру с лучшими путями
*/

void			ft_find_all_ways(t_data *data)
{
	t_option	*ptr;
	int			best_steps;
	t_option	*best_opt;

	while ((data->total_ways = find_ways(data->start, data->end)) > 0
			&& ft_suurballe(data))
	{
		--data->total_ways;
		find_of_ways_struct(data);
	}
	(!data->options || (data->options && !data->options->ways)) ?
				ft_print_error(E_PATH) : 1;
	ptr = data->options;
	best_steps = ptr->steps;
	best_opt = ptr;
	while ((ptr = ptr->next))
		if (ptr->steps <= best_steps)
		{
			best_steps = ptr->steps;
			best_opt = ptr;
		}
	data->best_opt = best_opt;
}
