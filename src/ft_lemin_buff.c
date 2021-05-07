/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:21:00 by asmall            #+#    #+#             */
/*   Updated: 2021/01/09 16:57:57 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_step_and_ant(char *room_name, int ants, int i)
{
	while (++i <= ants)
	{
		ft_printf("L%d-%s ", i, room_name);
		ft_printf("\n");
	}
}

void	add_ant_in_buff(t_way *way, int i)
{
	t_ants	*new;

	new = (t_ants *)ft_memalloc(sizeof(t_ants));
	if (!new)
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

void	write_in_buff(t_way *way, int count)
{
	t_way	*head;

	head = way;
	while (1)
	{
		if (way->ants)
			add_ant_in_buff(way, count++);
		way = way->next;
		if (!check_empty(head))
			break ;
		else if (!way)
			way = head;
	}
}

void	ft_lala(t_data *data, t_way *way)
{
	int		count;
	int		step;
	t_way	*head;

	step = 0;
	count = 1;
	write_in_buff(way, count);
	while (count && ++step)
	{
		count = 0;
		head = data->ways;
		while (head)
		{
			count += print_step(&(head)->buf, step);
			head = head->next;
			if (count && !head)
				ft_printf("\n");
		}
	}
}

void	ft_buff_lem(t_data *data, t_way *way)
{
	if (!data->ways)
	{
		ft_print_error(E_PATH);
		free_list(data->ways);
	}
	if (data->ways->len == 2)
	{
		print_step_and_ant(data->ways->path->next->room->name, data->ants, 0);
		free_list(data->ways);
		return ;
	}
	ft_lala(data, way);
	free_list(data->ways);
}
