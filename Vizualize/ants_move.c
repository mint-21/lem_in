/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:16:03 by asmall            #+#    #+#             */
/*   Updated: 2020/09/18 14:16:05 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

double			calc_diff(t_vis_ants ant, char axis)
{
	double		diff;

	diff = 0;
	if (axis == 'x')
		diff = ft_abs(ant.next_room.x - ant.current_room.x);
	else
		diff = ft_abs(ant.next_room.y - ant.current_room.y);
	return (diff);
}

void			print_ants(t_vis_ants *array)
{
	int			i;

	i = -1;
	while (++i < g_s.ants)
		if (array[i].next_room_name)
			push_ant_texture_to_render(array[i].current_room);
}

int				if_turn_over(t_vis_ants **array, t_data *g_s)
{
	t_vis_rooms	*current;
	int			i;

	if (g_s->flag)
		g_s->split = ft_strsplit(g_s->map_data, '\n');
	while (g_s->flag && g_s->split[g_s->step][0] != 'L')
		g_s->step += 1;
	g_s->flag = 0;
	if (!g_s->split[g_s->step])
		return (0);
	parse_turns_line(array, &g_s);
	i = -1;
	current = g_vis_rooms;
	while (++i < g_s->ants && current)
		if ((*array)[i].next_room_name)
		{
			while (ft_strcmp((*array)[i].next_room_name, current->name) != 0
				&& current)
				current = current->next;
			(*array)[i].next_room = current->room;
			current = g_vis_rooms;
		}
	return (1);
}

int				ants_move(t_vis_ants *array, int null_count)
{
	int			i;

	i = -1;
	while (++i < g_s.ants)
		if (array[i].next_room_name)
		{
			if (array[i].x_diff == 0 && array[i].y_diff == 0)
			{
				array[i].x_diff = (array[i].next_room.x -
					array[i].current_room.x) / SCREEN_FPS;
				array[i].y_diff = (array[i].next_room.y -
					array[i].current_room.y) / SCREEN_FPS;
			}
			array[i].current_room.x += array[i].x_diff;
			array[i].current_room.y += array[i].y_diff;
			if (calc_diff(array[i], 'x') <= 1 && calc_diff(array[i], 'y') <= 1
				&& array[i].next_room_name)
				null_ptr_ant(&array[i], &null_count);
		}
		else
			null_count++;
	return (null_count);
}
