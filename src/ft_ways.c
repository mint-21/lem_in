/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ways.c                                          :+:      :+:    :+:   */
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

static int		ft_min_steps_for_ants(t_way *way, int ants)
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
** В структуру data создаем структуру с лучшими вариантами пути
*/

static void		ft_cmp_options(t_data *data)
{
	t_option	*ptr;
	int			best_steps;
	t_option	*best_opt;

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

/*
** Считает количество связей с start и количество связей, приходящих в end
** Функция возвращает наименьшее из подсчитанных значений.
*/

static int		number_of_paths(t_room *start, t_room *end)
{
	int			i;
	int			j;
	t_link		*ptr;

	i = 0;
	ptr = start->links;
	while (ptr)
	{
		++i;
		ptr = ptr->next;
	}
	j = 0;
	ptr = end->links;
	while (ptr)
	{
		++j;
		ptr = ptr->next;
	}
	return ((j < i) ? j : i);
}

/*
** number_of_paths: возвращает количество путей
** ft_suurballe: ф-ия создает новый граф с входящими и исходящими узлами
** ft_paths_ascending: инициализируем струтуру new_ways и находим
** кратчайшие пути в новом графе
** ft_min_steps_for_ants: количество шагов от start до end
** ft_cmp_options: в главную структуру добавляем структуру с лучшими путями
** --data->ways_count: удаляем количество найденных путей
*/

void			init_var(t_option *var, t_way *new_ways, int new_steps)
{
	var->ways = new_ways;
	var->steps = new_steps;
	var->next = NULL;
}

void			ft_ways(t_data *data)
{
	t_way		*new_ways;
	int			new_steps;
	t_option	*var;

	new_steps = 0;
	data->ways_count = number_of_paths(data->start, data->end);
	while (data->ways_count > 0 && ft_suurballe(data))
	{
		--data->ways_count;
		if ((new_ways = ft_paths_ascending(data->start, data->end)))
			new_steps = ft_min_steps_for_ants(new_ways, data->ants);
		!(var = (t_option *)malloc(sizeof(t_option))) ? ft_perror() : 0;
		init_var(var, new_ways, new_steps);
		if (!data->options)
			data->options = var;
		else
		{
			var->next = data->options;
			data->options = var;
		}
	}
	(!data->options || (data->options && !data->options->ways)) ?
				ft_print_error(E_PATH) : 1;
	ft_cmp_options(data);
}
