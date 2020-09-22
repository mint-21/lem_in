/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:09 by asmall            #+#    #+#             */
/*   Updated: 2020/09/22 12:01:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

int		init_sdl(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error("SDL could not initialize. SDL error: ", SDL_GetError());
	g_main_window = SDL_CreateWindow("Lem_in", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_main_window == NULL)
		error("SDL could not create window. SDL error: ", SDL_GetError());
	g_main_render = SDL_CreateRenderer(g_main_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (g_main_render == NULL)
		error("Renderer could not be created! SDL Error: ", SDL_GetError());
	if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
		error("SDL_image couldn't initialize. SDL error: ", IMG_GetError());
	if (TTF_Init() < 0)
		error("SDL_ttf couldn't initialize. SDL error: ", TTF_GetError());
	return (1);
}

void	color_and_coord(t_vis_rooms *vis_room, t_room *current_s_room, t_data s)
{
	vis_room->room.x = ft_abs(current_s_room->x * (SCREEN_WIDTH /
		(MAX(ft_find_max_x(s), 1))) - 50);
	vis_room->room.y = ft_abs(current_s_room->y * (SCREEN_HEIGHT /
		(MAX(ft_find_max_y(s), 1))) - 50);
	vis_room->name = current_s_room->name;
	vis_room->num = current_s_room->n;
	vis_room->r = rand() % 255 + 1;
	vis_room->g = rand() % 255 + 1;
	vis_room->b = rand() & 255 + 1;
	SDL_SetRenderDrawColor(g_main_render, vis_room->r,
		vis_room->g, vis_room->b, 100);
	SDL_RenderFillRectF(g_main_render, &vis_room->room);
}

int		close_sdl(void)
{
	free(g_vis_rooms);
	SDL_DestroyWindow(g_main_window);
	g_main_window = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return (0);
}
