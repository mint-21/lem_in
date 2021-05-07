/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_funct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:28 by asmall            #+#    #+#             */
/*   Updated: 2021/05/07 16:03:27 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	calc_max_xy(t_data s, int flag)
{
	int			max;
	t_room		*curr;

	max = -MAX_INT - 1;
	curr = s.rooms;
	while (curr && flag == 1)
	{
		if (curr->x > max)
			max = curr->x;
		curr = curr->next;
	}
	while (curr && flag == 2)
	{
		if (curr->y > max)
			max = curr->y;
		curr = curr->next;
	}
	return (max);
}

void	ant_on_null(t_ants_v *ant, int *null_count)
{
	(*ant).x_diff = 0;
	(*ant).y_diff = 0;
	(*ant).curr_room = (*ant).next_room;
	(*ant).next_name = NULL;
	(*null_count)++;
}

t_room_v	*init_vis_room(void)
{
	t_room_v	*room;

	room = (t_room_v *)malloc(sizeof(t_room_v));
	if (!(room))
		return (NULL);
	room->next = NULL;
	room->room.x = 0;
	room->room.y = 0;
	room->room.h = 50;
	room->room.w = 50;
	room->name = NULL;
	room->num = 0;
	return (room);
}

t_ants_v	*array_vis_ants(t_data s)
{
	t_ants_v	*array;
	t_room_v	*curr;
	int			i;

	i = -1;
	array = (t_ants_v *)malloc(sizeof(t_ants_v) * s.ants);
	curr = g_vis_rooms;
	while (curr && curr->num != s.start->n)
		curr = curr->next;
	while (++i < s.ants)
	{
		array[i].curr_room = curr->room;
		array[i].next_room.h = 50;
		array[i].next_room.w = 50;
		array[i].next_room.x = 0;
		array[i].next_room.y = 0;
		array[i].x_diff = 0;
		array[i].y_diff = 0;
		array[i].curr_name = curr->name;
		array[i].next_name = NULL;
	}
	return (array);
}
