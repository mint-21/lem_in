/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:00:00 by asmall            #+#    #+#             */
/*   Updated: 2020/08/04 17:00:01 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** We count the number of steps along the way
** steps - (way->path_cost - 1): number of steps to revise
** ((tmp * (way->path_number - 1)) + ost) / way->path_number: calculation of
** a new number of steps
** (tmp * (way->path_number - 1) + ost) % way->path_number: number of ant in
** the remainder
** The function returns the number of steps taken.
*/

int				steps_for_ants(t_way *way, int ants)
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
** The function looks for the room where the ant currently exists
** ++way->ants: counting the number of ants passing through the path
** way = way->next: if there is more than one path, we take the next path
*/

void			ft_step(t_data *data, int *ant, t_buf *buf, int steps)
{
	t_way		*way;
	t_path		*path;

	buf->space = 0;
	way = data->best_opt->ways;
	while (way)
	{
		path = way->path;
		while (path)
		{
			if (path->room == data->start && data->start->ant &&
			(way->path_cost <= steps || way->path_number == 1))
			{
				copy_text_buff(data, path, buf, ++*ant);
				++way->ants;
			}
			else if (path->room != data->start && path->room != data->end
			&& path->room->ant)
				copy_text_buff(data, path, buf, path->room->ant);
			path = path->next;
		}
		way = way->next;
	}
}
