/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:28:23 by asmall            #+#    #+#             */
/*   Updated: 2020/05/13 19:28:53 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			print_n_free_map_data(char **map_data)
{
	ft_printf("%s\n", *map_data);
	free(*map_data);
}

static void		print_ways(t_way *way)
{
	t_path		*ptr;

	ft_printf("%5d | ", way->ants);
	ptr = way->path;
	while (ptr && ptr->next)
		ptr = ptr->next;
	while (ptr)
	{
		ft_printf("%s", ptr->room->name);
		if (ptr->prev)
			ft_printf(" - ");
		else
			ft_printf("\n");
		ptr = ptr->prev;
	}
}

void			ft_print_ways(t_way *way, int steps)
{
	t_way		*w;
	int			total_ways;

	w = way;
	if (w->ants)
		total_ways = 1;
	while ((w = w->next) && w->ants)
		++total_ways;
	ft_printf("Total lines: %d\nTotal ways:  %d\n"
			" ANTS | WAYS\n", steps, total_ways);
	while (way && way->ants > 0)
	{
		print_ways(way);
		way = way->next;
	}
}
