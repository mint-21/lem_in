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
** ft_paths_ascending: инициализируем струтуру new_ways и находим
** кратчайшие пути в новом графе
** ft_min_steps_for_ants: количество шагов от start до end
*/

void			find_of_ways_struct(t_data *data)
{
	t_way		*new_ways;
	int			new_steps;
	t_option	*var;
	t_connect	*t_h;
	t_connect	*t_t;

	new_steps = 0;
	t_h = data->end->connects;
	while (t_h && t_h->weight != -1)
		t_h = t_h->next;
	if (!t_h)
		exit (0);
	t_t = t_h;
	ft_connect_end(&t_h, &t_t);
	new_ways = ft_ways_ascending(t_h, t_t, data->start, data->end);
	null_turn(t_h, t_t, data->end);
	if (new_ways)
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
