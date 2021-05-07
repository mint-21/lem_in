/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:09 by asmall            #+#    #+#             */
/*   Updated: 2021/05/07 13:31:33 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

int	init_sdl(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error("SDL could not initialize. SDL error: ", SDL_GetError());
	g_main_window = SDL_CreateWindow("Lem_in", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
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

void	color_and_coord(t_room_v *vis_room, t_room *current_s_room, t_data s)
{
	vis_room->room.x = ft_abs(current_s_room->x * (SCREEN_WIDTH
				/ (ft_max(calc_max_xy(s, 1), 1))) - 50);
	vis_room->room.y = ft_abs(current_s_room->y * (SCREEN_HEIGHT
				/ (ft_max(calc_max_xy(s, 2), 1))) - 50);
	vis_room->name = current_s_room->name;
	vis_room->num = current_s_room->n;
	vis_room->r = rand() % 255 + 1;
	vis_room->g = rand() % 255 + 1;
	vis_room->b = rand() & 255 + 1;
	SDL_SetRenderDrawColor(g_main_render, vis_room->r,
		vis_room->g, vis_room->b, 100);
	SDL_RenderFillRectF(g_main_render, &vis_room->room);
}

int	close_sdl(void)
{
	ft_struct_free(&g_struct);
	free(g_vis_rooms);
	SDL_DestroyWindow(g_main_window);
	g_main_window = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return (0);
}

void	create_name_room(t_room_v *vis_room, t_room *norm_room,
			TTF_Font *courier)
{
	SDL_Rect	name_rect;

	TTF_SizeText(courier, norm_room->name, &name_rect.w, &name_rect.h);
	name_rect.x = (int)vis_room->room.x;
	name_rect.y = (int)vis_room->room.y;
	SDL_RenderCopy(g_main_render,
		SDL_CreateTextureFromSurface(g_main_render,
			TTF_RenderText_Solid(courier, norm_room->name,
				(SDL_Color){0, 0, 0, 255})), NULL, &name_rect);
}
