/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_funct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:28 by asmall            #+#    #+#             */
/*   Updated: 2020/09/22 12:07:30 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

int				ft_find_max_x(t_data s)
{
	int			max;
	t_room		*curr;

	max = -MAX_INT - 1;
	curr = s.rooms;
	while (curr)
	{
		if (curr->x > max)
			max = curr->x;
		curr = curr->next;
	}
	return (max);
}

int				ft_find_max_y(t_data s)
{
	int			max;
	t_room		*curr;

	max = -MAX_INT - 1;
	curr = s.rooms;
	while (curr)
	{
		if (curr->y > max)
			max = curr->y;
		curr = curr->next;
	}
	return (max);
}

void			null_ptr_ant(t_vis_ants *ant, int *null_count)
{
	(*ant).x_diff = 0;
	(*ant).y_diff = 0;
	(*ant).current_room = (*ant).next_room;
	(*ant).next_name = NULL;
	(*null_count)++;
}

t_vis_rooms		*make_new_vis_room(void)
{
	t_vis_rooms	*room;

	if (!(room = (t_vis_rooms *)malloc(sizeof(t_vis_rooms))))
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

t_vis_ants		*make_new_vis_ants_array(t_data s)
{
	t_vis_ants	*array;
	t_vis_rooms	*curr;
	int			i;

	array = (t_vis_ants *)malloc(sizeof(t_vis_ants) * s.ants);
	curr = g_vis_rooms;
	while (curr && curr->num != s.start->n)
		curr = curr->next;
	i = -1;
	while (++i < s.ants)
	{
		array[i].current_room = curr->room;
		array[i].next_room.h = 50;
		array[i].next_room.w = 50;
		array[i].next_room.x = 0;
		array[i].next_room.y = 0;
		array[i].x_diff = 0;
		array[i].y_diff = 0;
		array[i].current_name = curr->name;
		array[i].next_name = NULL;
	}
	return (array);
}
