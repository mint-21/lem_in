/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_of_ways_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:00:00 by asmall            #+#    #+#             */
/*   Updated: 2020/07/04 17:32:01 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Building the ways path structure
** create_inhead: creating incoming nodes
** find the shortest paths in the new graph with their weight
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
** Find the shortest paths on the new graph and enter into the structure
** Flip the ribs from end to start and find ways
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

static void		init_var(t_option *var, t_way *new_ways,
							int new_steps, t_data *data)
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
** reverse_h, reverse_t: back edges (ribs).
** ft_connect_end: connection with the room end.
** null_turn: removal of back edges (ribs).
** steps_for_ants: number of steps from start to end
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
		exit(0);
	reverse_t = reverse_h;
	ft_connect_end(&reverse_h, &reverse_t);
	new_ways = flip_ribs(reverse_h, reverse_t, data->start, data->end);
	null_turn(reverse_h, reverse_t, data->end);
	if (new_ways)
		new_steps = steps_for_ants(new_ways, data->ants);
	!(var = (t_option *)malloc(sizeof(t_option))) ? ft_perror() : 0;
	init_var(var, new_ways, new_steps, data);
}
