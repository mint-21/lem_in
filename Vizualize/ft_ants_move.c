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
		if (array[i].next_name)
			render_texture_png(array[i].current_room);
}

int				if_turn_over(t_vis_ants **array, t_data *g_s)
{
	t_vis_rooms	*curr;
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
	curr = g_vis_rooms;
	while (++i < g_s->ants && curr)
		if ((*array)[i].next_name)
		{
			while (ft_strcmp((*array)[i].next_name, curr->name) != 0
				&& curr)
				curr = curr->next;
			(*array)[i].next_room = curr->room;
			curr = g_vis_rooms;
		}
	return (1);
}

int				ants_move(t_vis_ants *array, int null_count)
{
	int			i;

	i = -1;
	while (++i < g_s.ants)
		if (array[i].next_name)
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
				&& array[i].next_name)
				null_ptr_ant(&array[i], &null_count);
		}
		else
			null_count++;
	return (null_count);
}

void			start_process(t_vis_ants *array)
{
	int			count;

	count = 0;
	while (!g_s.vis_quit)
	{
		event_handler(&g_s);
		if (!g_s.vis_pause)
		{
			count = ants_move(array, 0);
			render_process(g_s, NULL);
			if (count == g_s.ants)
			{
				if (!if_turn_over(&array, &g_s))
					break ;
			}
			else
				print_ants(array);
			SDL_Delay(SCREEN_TICKS_PER_FRAME);
			SDL_RenderPresent(g_main_render);
		}
	}
}
