/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ants_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:11:21 by asmall            #+#    #+#             */
/*   Updated: 2020/09/21 13:11:37 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

double			math_different(t_ants_v ant, char axis)
{
	double		diff;

	diff = 0;
	diff = (axis == 'x') ? (ft_abs(ant.next_room.x - ant.curr_room.x)) :
		(ft_abs(ant.next_room.y - ant.curr_room.y));
	return (diff);
}

void			print_ants(t_ants_v *array)
{
	int			i;

	i = -1;
	while (++i < g_struct.ants)
		if (array[i].next_name)
			render_texture_png(array[i].curr_room);
}

int				if_turn_over(t_ants_v **array, t_data *g_struct)
{
	t_room_v	*curr;
	int			i;

	if (g_struct->flag)
		g_struct->split = ft_strsplit(g_struct->map_data, '\n');
	while (g_struct->flag && g_struct->split[g_struct->step][0] != 'L')
		g_struct->step += 1;
	g_struct->flag = 0;
	if (!g_struct->split[g_struct->step])
		return (0);
	turn_line(array, &g_struct);
	i = -1;
	curr = g_vis_rooms;
	while (++i < g_struct->ants && curr)
		if ((*array)[i].next_name)
		{
			while (ft_strcmp((*array)[i].next_name, curr->name) != 0 && curr)
				curr = curr->next;
			(*array)[i].next_room = curr->room;
			curr = g_vis_rooms;
		}
	return (1);
}

int				ants_move(t_ants_v *array, int null_count)
{
	int			i;

	i = -1;
	while (++i < g_struct.ants)
		if (array[i].next_name)
		{
			if (array[i].x_diff == 0 && array[i].y_diff == 0)
			{
				array[i].x_diff = (array[i].next_room.x -
					array[i].curr_room.x) / STEP_SCREEN;
				array[i].y_diff = (array[i].next_room.y -
					array[i].curr_room.y) / STEP_SCREEN;
			}
			array[i].curr_room.x += array[i].x_diff;
			array[i].curr_room.y += array[i].y_diff;
			if (math_different(array[i], 'x') <= 1
				&& math_different(array[i], 'y') <= 1 && array[i].next_name)
				ant_on_null(&array[i], &null_count);
		}
		else
			null_count++;
	return (null_count);
}

void			start_process(t_ants_v *array)
{
	int			count;

	count = 0;
	while (!g_struct.vis_quit)
	{
		event_handler(&g_struct);
		if (!g_struct.vis_pause)
		{
			count = ants_move(array, 0);
			render_process(g_struct, NULL);
			if (count == g_struct.ants)
			{
				if (!if_turn_over(&array, &g_struct))
					break ;
			}
			else
				print_ants(array);
			SDL_Delay(SCREEN_TICKS_PER_FRAME);
			SDL_RenderPresent(g_main_render);
		}
	}
}
