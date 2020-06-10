/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_all_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:37:00 by vfearles          #+#    #+#             */
/*   Updated: 2020/05/13 19:31:48 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Считаем количество шагов в пути
** steps - (way->path_cost - 1): количество шагов подлежащее пересмотру
** ((tmp * (way->path_number - 1)) + ost) / way->path_number: расчет нового
** кол-ва шагов для пути
** (tmp * (way->path_number - 1) + ost) % way->path_number: кол-во мурав в ост
** Функция возвращает количество пройденных шагов.
*/

int		ft_min_steps_for_ants(t_way *way, int ants)
{
	int			steps;
	int			ost;
	int			tmp;

	steps = 0;
	ost = 0;
	while (way)
	{
		if (!way->prev)
			steps = way->path_cost + ants - 1;
		else if (steps > way->path_cost)
		{
			tmp = steps - (way->path_cost - 1);
			steps = steps - tmp;
			tmp = (ost) ? tmp - 1 : tmp;
			steps += ((tmp * (way->path_number - 1)) + ost) / way->path_number;
			ost = (tmp * (way->path_number - 1) + ost) % way->path_number;
			steps = (ost) ? steps + 1 : steps;
		}
		else if (steps <= way->path_cost)
			break ;
		way = way->next;
	}
	return (steps);
}

/*
** Считает количество связей с start и количество связей, приходящих в end
** Функция возвращает наименьшее из подсчитанных значений.
*/

static int		find_ways(t_link *start, t_link *end)
{
	int			i;
	int			j;

	i = 0;
	while (start)
	{
		++i;
		start = start->next;
	}
	j = 0;
	while (end)
	{
		++j;
		end = end->next;
	}
	return ((j < i) ? j : i);
}

void			init_var(t_option *var, t_way *new_ways, int new_steps)
{
	var->ways = new_ways;
	var->steps = new_steps;
	var->next = NULL;
}

/*
** find_ways: возвращает количество путей
** ft_suurballe: ф-ия создает новый граф с входящими и исходящими узлами
** В главную структуру добавляем структуру с лучшими путями
*/

void			ft_find_all_ways(t_data *data)
{
	t_link		*end_link;
	t_link		*start_link;
	t_option	*ptr;
	int			best_steps;
	t_option	*best_opt;

	end_link = data->end->links;
	start_link = data->start->links;
	while ((data->total_ways = find_ways(start_link, end_link)) > 0
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
