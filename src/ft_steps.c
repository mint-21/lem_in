/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_steps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:00:00 by asmall            #+#    #+#             */
/*   Updated: 2020/08/04 17:00:01 by vfearles         ###   ########.fr       */
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

int		steps_for_ants(t_way *way, int ants)
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
** Функция ищет комнату, где на данный момент есть муравей.
** В path и way передали лучший путь.
** ++way->ants: подчсчет кол-ва муравьев проходящих через путь.
** copy_text_buff: заносит в буфер текст и ведет подсчет
** муравьев в каждой комнате.
** way = way->next: если путь не один, берем следубщий путь.
*/

void	ft_step(t_data *data, int *ant, t_buf *buf, int steps)
{
	t_way	*way;
	t_path	*path;

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
