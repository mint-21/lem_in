/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_ascending.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:00:00 by vfearles          #+#    #+#             */
/*   Updated: 2019/12/04 17:00:01 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_connect_end(t_connect **turn_head, t_connect **turn_tail)
{
	t_connect	*connect;

	connect = (*turn_head)->next;
	while (connect)
	{
		if (connect->weight == -1)
		{
			(*turn_tail)->turn_next = connect;
			*turn_tail = (*turn_tail)->turn_next;
		}
		connect = connect->next;
	}
}

static void		init_var(t_option *var, t_way *new_ways, int new_steps)
{
	var->ways = new_ways;
	var->steps = new_steps;
	var->next = NULL;
}

/*
** turn_head, turn_tail: обратные края (ребра).
** ft_ways_ascending: поиск кратчайших путей.
** ft_connect_end: связи с комнатой end.
** null: удаление обратных краев (ребер).
*/

t_way			*ft_paths_ascending(t_room *start, t_room *end)
{
	t_connect	*turn_head;
	t_connect	*turn_tail;
	t_way	*ways_begin;

	turn_head = end->connects;
	while (turn_head && turn_head->weight != -1)
		turn_head = turn_head->next;
	if (!turn_head)
		return (NULL);
	turn_tail = turn_head;
	ft_connect_end(&turn_head, &turn_tail);
	ways_begin = ft_ways_ascending(turn_head, turn_tail, start, end);
	null_turn(turn_head, turn_tail, end);
	return (ways_begin);
}

/*
** ft_paths_ascending: инициализируем струтуру new_ways и находим
** кратчайшие пути в новом графе
** ft_min_steps_for_ants: количество шагов от start до end
*/

void			find_of_ways_struct(t_data *data)
{
	t_way		*new_ways;
	int			new_steps;
	t_option	*var;

	new_steps = 0;
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
