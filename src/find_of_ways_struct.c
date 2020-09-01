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

static void		ft_connect_end(t_connect **reverse_h, t_connect **reverse_t)
{
	t_connect	*connect;

	connect = (*reverse_h)->next;
	while (connect)
	{
		if (connect->weight == -1)
		{
			(*reverse_t)->turn_next = connect;
			*reverse_t = (*reverse_t)->turn_next;
		}
		connect = connect->next;
	}
}

static void		init_var(t_option *var, t_way *new_ways, int new_steps, t_data *data)
{
	var->ways = new_ways;
	var->steps = new_steps;
	var->next = NULL;
	if (!data->options)
		data->options = var;
	else
	{
		var->next = data->options;
		data->options = var;
	}
}

/*
** reverse_h, reverse_t: обратные края (ребра).
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
	t_connect	*reverse_h;
	t_connect	*reverse_t;

	new_steps = 0;
	reverse_h = data->end->connects;
	while (reverse_h && reverse_h->weight != -1)
		reverse_h = reverse_h->next;
	if (!reverse_h)
		exit (0);
	reverse_t = reverse_h;
	ft_connect_end(&reverse_h, &reverse_t);
	new_ways = ft_ways_ascending(reverse_h, reverse_t, data->start, data->end); // иземнить ft_ways_ascending
	null_turn(reverse_h, reverse_t, data->end);
	if (new_ways)
		new_steps = ft_min_steps_for_ants(new_ways, data->ants); // изменить ft_min_steps_for_ants
	!(var = (t_option *)malloc(sizeof(t_option))) ? ft_perror() : 0;
	init_var(var, new_ways, new_steps, data);
}
