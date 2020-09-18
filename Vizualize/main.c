/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:00:10 by qmebble           #+#    #+#             */
/*   Updated: 2019/09/18 21:45:24 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

void		push_all_to_render(t_data s, t_vis_ants **array)
{
	t_vis_rooms	*current;

	current = g_vis_rooms;
	SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
	SDL_RenderClear(g_main_render);
	while (current)
	{
		SDL_SetRenderDrawColor(g_main_render, current->r,
								current->g, current->b, 100);
		SDL_RenderFillRectF(g_main_render, &current->room);
		current = current->next;
	}
	push_links_ro_render(s);
	if (array)
		*array = make_new_vis_ants_array(s);
	push_names_ro_render(s);
}

double		calc_diff(t_vis_ants ant, char axis)
{
	double	diff;

	diff = 0;
	if (axis == 'x')
		diff = ft_abs(ant.next_room.x - ant.current_room.x);
	else
		diff = ft_abs(ant.next_room.y - ant.current_room.y);
	return (diff);
}

void		null_ptr_ant(t_vis_ants *ant, int *null_count)
{
	(*ant).x_diff = 0;
	(*ant).y_diff = 0;
	(*ant).current_room = (*ant).next_room;
	(*ant).next_room_name = NULL;
	(*null_count)++;
}

void		print_data_debug(t_vis_ants ant, int i)
{
	ft_printf("current_room = %s\n", ant.current_room_name);
	ft_printf("next_room name = %s\n", ant.next_room_name);
	ft_printf("ants num = %d\n", i + 1);
	ft_printf("x_dif = %f, y_diff = %f\n\n", ant.x_diff, ant.y_diff);
}

int			ants_move(t_vis_ants *array, int null_count)
{
	int	i;

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
			if (g_debug)
				print_data_debug(array[i], i);
			if (calc_diff(array[i], 'x') <= 1 && calc_diff(array[i], 'y') <= 1
				&& array[i].next_room_name)
				null_ptr_ant(&array[i], &null_count);
		}
		else
			null_count++;
	return (null_count);
}

void		pause_for_debug(void)
{
	SDL_Event	event;

	if (!g_debug)
		return ;
	while (1)
		if(SDL_PollEvent(&event))
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_RETURN
					|| event.key.keysym.sym == SDLK_ESCAPE)
					break ;
}

void		print_ants(t_vis_ants *array)
{
	int	i;

	i = -1;
	while (++i < g_s.ants)
		if (array[i].next_room_name)
			push_ant_texture_to_render(array[i].current_room);
}

int			initialize_data(int argc, char **argv)
{
	char	**str_split;

	g_s = ft_zerodata();
	g_s.map_data = ft_lemin_read(&g_s.flags, &str_split);
	ft_correct(&g_s, &g_s.check, str_split);
	ft_find_all_ways(&g_s);
	if (g_s.rooms_count > 50)
	{
		printf("Too many rooms\n");
		return (0);
	}
	srand(time(NULL));
	g_main_window = NULL;
	g_main_render = NULL;
	if (!init())
		return (close_all());
	g_vis_rooms = push_rooms_to_render(g_s);
	g_debug = false;
	if (argc == 2)
		if (ft_strcmp(argv[1], "--debug") == 0)
			g_debug = true;
	return (1);
}

int			if_turn_over(t_vis_ants **array, t_data *g_s)
{
	t_vis_rooms	*current;
	int	i;

	if (parse_turns_line(array, &g_s)) { 
		printf("\n\n\n\n\n|||||||PARSE|||||||\n\n\n");
		return (0); }
	i = -1;
	current = g_vis_rooms;
	while (++i < g_s->ants && current)
		if ((*array)[i].next_room_name)
		{
			while(ft_strcmp((*array)[i].next_room_name, current->name) != 0 && current)
				current = current->next;
			(*array)[i].next_room = current->room;
			current = g_vis_rooms;
		}
	pause_for_debug();
	return (1);
}

int			main(int argc, char **argv)
{
	int			NULL_count;
	t_vis_ants	*array;
	SDL_Event	event;
	bool		quit;
	t_vis_rooms	*end_room;

	if (!initialize_data(argc, argv))
		return (0);
	end_room = g_vis_rooms;
	while (end_room && end_room->num != g_s.end->n)
		end_room = end_room->next;
	quit = false;
	push_all_to_render(g_s, &array);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
		NULL_count = ants_move(array, 0);
		push_all_to_render(g_s, NULL);
		if (NULL_count == g_s.ants)
		{
			if (!if_turn_over(&array, &g_s))
				break ;
		}
		else 
			print_ants(array);
		SDL_Delay(SCREEN_TICKS_PER_FRAME);
		SDL_RenderPresent(g_main_render);
	}
	pause_for_debug();
	return (close_all());
}
