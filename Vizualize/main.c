/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:59:36 by asmall            #+#    #+#             */
/*   Updated: 2020/09/21 12:59:40 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

void			error(const char *s, const char *t)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, t, ft_strlen(t));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void			push_all_to_render(t_data s, t_vis_ants **array)
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
	push_links_ro_render(s, -1);
	if (array)
		*array = make_new_vis_ants_array(s);
	push_names_ro_render(s);
}

int				initialize(void)
{
	char		**str_split;

	g_s = ft_zerodata();
	g_s.map_data = reading_card(&g_s.flags, &str_split);
	ft_correct(&g_s, &g_s.check, str_split);
	if (g_s.rooms_count > 50)
	{
		printf("Too many rooms\n");
		return (0);
	}
	srand(time(NULL));
	if (!init())
		return (close_all());
	g_vis_rooms = push_rooms_to_render(g_s);
	return (1);
}

void			event_handler(t_data *g_s)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
			g_s->vis_pause = !g_s->vis_pause;
		else if (event.type == SDL_QUIT ||
		(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			g_s->vis_quit = 1;
	}
}

int				main(void)
{
	t_vis_ants	*array;
	t_vis_rooms	*end_room;

	if (!initialize())
		return (0);
	end_room = g_vis_rooms;
	while (end_room && end_room->num != g_s.end->n)
		end_room = end_room->next;
	push_all_to_render(g_s, &array);
	start_process(array);
	return (close_all());
}
