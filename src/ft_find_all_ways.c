/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_all_ways.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:37:00 by asmall            #+#    #+#             */
/*   Updated: 2020/08/13 19:31:48 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Counts the number of links from start and the number of links coming to end
** The function returns the smallest of the counted values
*/

int					count_links(t_room *r)
{
	t_connect		*ptr;
	int				ret;

	ret = 0;
	ptr = r->connects;
	while (ptr)
	{
		ptr = ptr->next;
		ret++;
	}
	return (ret);
}

static int			find_ways(t_room *start, t_room *end)
{
	int connect_start;
	int connect_end;

	connect_start = count_links(start);
	connect_end = count_links(end);
	if (connect_start > connect_end)
		return (connect_end);
	return (connect_start);
}

/*
** find_ways: returns the number of paths
** ft_srb_alg: function creates a new graph with incoming and outgoing nodes
** add structure with better paths
*/

void				ft_find_all_ways(t_data *data)
{
	t_option		*ptr;
	int				best_steps;
	t_option		*best_opt;

	while ((data->total_ways = find_ways(data->start, data->end)) > 0
			&& ft_srb_alg(data))
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
