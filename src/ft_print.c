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

void	ft_print_error(int id)
{
	if (id == 1)
		ft_printf("{red}%s\n", "ERROR: memory problems");
	if (id == 2)
		ft_printf("{red}%s\n", "ERROR: using forbidden characters");
	if (id == 3)
		ft_printf("{red}%s\n", "ERROR: in start initialization");
	if (id == 4)
		ft_printf("{red}%s\n", "ERROR: in end initialization");
	if (id == 5)
		ft_printf("{red}%s\n", "ERROR: ants parameter not valid");
	if (id == 6)
		ft_printf("{red}%s\n", "ERROR: room connections are not valid");
	if (id == 7)
		ft_printf("{red}%s\n", "ERROR: the card has no solution");
	if (id == 8)
		ft_printf("{red}%s\n", "ERROR: comments are not valid");
	if (id == 9)
		ft_printf("{red}%s\n", "ERROR: room names are not valid");
	if (id == 10)
		ft_printf("{red}%s\n", "ERROR: coordinates of rooms are not valid");
	exit(id);
}

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

void			ft_clean_links(t_data *s)
{
	t_link		*cur_l;
	t_link		*next_l;
	int			i;

	i = -1;
	while (++i < s->rooms_count)
	{
		cur_l = s->links[i];
		while (cur_l)
		{
			next_l = cur_l->next;
			free(cur_l);
			cur_l = next_l;
		}
	}
	free(s->links);
}
