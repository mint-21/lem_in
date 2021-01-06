/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:21:00 by asmall            #+#    #+#             */
/*   Updated: 2021/01/06 20:08:38 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_step_and_ant(char *name, int ants, int i)
{
	while (i++ <= ants)
	{
		ft_printf("L%d-%s ", i, name);
		ft_printf("\n");
	}
}

void		add_in_buff(t_way *way, int i)
{
	t_ants	*new;

	if (!(new = (t_ants *)ft_memalloc(sizeof(t_ants))))
		exit(1);
	way->ants -= 1;
	new->num = i;
	new->curr = way->path;
	if (!(way->last_ant))
		way->buf = new;
	else
		way->last_ant->next = new;
	way->last_ant = new;
}

void		ft_buff_lem(t_data *data, t_way *way)
{
	int		count;
	t_way	*head;

	if (data->ways->len == 2)
	{
		print_step_and_ant(data->ways->path->next->room->name, data->ants, 0);
		free_list(data->ways);
		return ;
	}
	count = 1;
	head = data->ways;
	while (1)
	{
		if (way->ants)
			add_in_buff(way, count++);
		if (!check_empty(head))
			break ;
		else if (!(way = way->next))
			way = head;
	}
	count = 0;
	while (print_line(data->ways, ++count))
		ft_printf("\n");
	free_list(data->ways);
}
