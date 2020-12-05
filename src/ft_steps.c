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

int				steps_for_ants(t_way *way, int ants, int steps)
{
	int			ost;
	int			tmp;

	ost = 0;
	while (way)
	{
		if (!way->prev)
			steps = way->len + ants - 1;
		else if (steps > way->len)
		{
			tmp = steps - (way->len - 1);
			steps = steps - tmp;
			tmp = (ost) ? tmp - 1 : tmp;
			steps += ((tmp * (way->path_number - 1)) + ost) / way->path_number;
			ost = (tmp * (way->path_number - 1) + ost) % way->path_number;
			if (ost)
				steps++;
		}
		else if (steps <= way->len)
			break ;
		way = way->next;
	}
	return (steps);
}

/*
** The function looks for the room where the ant currently exists
** way = way->next: if there is more than one path, we take the next path
*/

int				ft_step(t_data *data, t_buf *buf, int steps, t_way *way)
{
	buf->space = 0;
	while (way)
	{
		terms_staps(way, data, steps, buf);
		way = way->next;
	}
	ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE, '\n');
	--steps;
	return (steps);
}
