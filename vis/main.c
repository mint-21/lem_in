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

void			render_process(t_data s, t_ants_v **array)
{
	t_room_v	*curr;

	curr = g_vis_rooms;
	SDL_SetRenderDrawColor(g_main_render, 255, 255, 255, 255);
	SDL_RenderClear(g_main_render);
	while (curr)
	{
		SDL_SetRenderDrawColor(g_main_render, curr->r, curr->g, curr->b, 100);
		SDL_RenderFillRectF(g_main_render, &curr->room);
		curr = curr->next;
	}
	render_links(s, -1);
	if (array)
		*array = array_vis_ants(s);
	render_name_room(s);
}

int				initialize(int fd)
{
	char		**str_split;

	g_struct = ft_zerodata();
	g_struct.map_data = reading_card(&str_split, fd);
	ft_correct(&g_struct, &g_struct.check, str_split);
	if (g_struct.rooms_count > 50)
	{
		ft_printf("Error: too many rooms\n");
		ft_struct_free(&g_struct);
		return (0);
	}
	if (!init_sdl())
		return (close_sdl());
	g_vis_rooms = render_rooms(g_struct);
	return (1);
}

void			event_handler(t_data *g_struct)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
			g_struct->vis_pause = !g_struct->vis_pause;
		else if (event.type == SDL_QUIT ||
		(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			g_struct->vis_quit = 1;
	}
}

int				main(int ac, char **av)
{
	t_ants_v	*array;
	t_room_v	*end_room;
	int fd;

    fd = 0;
    if (ac == 2)
        fd = open(av[1], O_RDONLY);
	if (!initialize(fd))
		return (0);
	end_room = g_vis_rooms;
	while (end_room && end_room->num != g_struct.end->n)
		end_room = end_room->next;
	render_process(g_struct, &array);
	start_process(array);
	return (close_sdl());
}
