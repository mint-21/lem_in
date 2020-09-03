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

/*
** Создаем структуру путей ways
** create_inhead: создаем входящие узлы
** находим кратчайшие пути в новом графе с их весом
*/

static t_way	*create_ways(t_connect *head, t_way *ways, t_room *end)
{
	t_path		*path;
	t_way		*way;
	t_path		*tmp;
	int			weight;

	weight = 0;
	path = NULL;
	while (head)
	{
		tmp = path;
		if (!(path = (t_path *)malloc(sizeof(t_path))))
			ft_perror();
		head = create_inhead(tmp, path, head, &weight);
	}
	tmp = path;
	if (!(path = (t_path *)malloc(sizeof(t_path))))
		ft_perror();
	path_init(path, end, tmp);
	if (tmp)
		tmp->prev = path;
	if (!(way = (t_way *)malloc(sizeof(t_way))))
		ft_perror();
	way = way_init(way, path, weight, ways);
	ways = way;
	return (ways);
}

/*
** Находим кратчайшие пути на новом графе и заносим в структуру
** create_ways: создание новой структуры для кратчайших путей
** Переворачиваем ребра от конца до старта и ищем пути
** terms: дополнительные условия
*/

static t_way	*flip_ribs(t_connect *head, t_connect *tail,
				t_room *start, t_room *end)
{
	t_connect	*connect;
	t_way		*ways;
	t_way		*ways_begin;

	ways = NULL;
	ways_begin = NULL;
	while (head)
	{
		connect = terms(head, connect);
		if (connect && connect->weight == -1)
		{
			tail->turn_next = connect;
			connect->parrent = head;
			tail = tail->turn_next;
		}
		if (head->room == start)
			ways = create_ways(head, ways, end);
		if (!ways_begin && ways)
			ways_begin = ways;
		head = head->turn_next;
	}
	return (ways_begin);
}

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
** flip_ribs: поиск кратчайших путей.
** ft_connect_end: связи с комнатой end.
** null: удаление обратных краев (ребер).
** ft_paths_ascending: инициализируем струтуру new_ways и находим
** кратчайшие пути в новом графе
** steps_for_ants: количество шагов от start до end
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
	new_ways = flip_ribs(reverse_h, reverse_t, data->start, data->end);
	null_turn(reverse_h, reverse_t, data->end);
	if (new_ways)
		new_steps = steps_for_ants(new_ways, data->ants);
	!(var = (t_option *)malloc(sizeof(t_option))) ? ft_perror() : 0;
	init_var(var, new_ways, new_steps, data);
}
