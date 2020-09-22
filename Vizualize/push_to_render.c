/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:00:09 by asmall            #+#    #+#             */
/*   Updated: 2020/09/21 13:00:12 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

bool			init(void)
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
	return (true);
}
void			color_and_coord(t_vis_rooms *vis_room,
					t_room *current_s_room, t_data s)
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

t_vis_rooms		*push_rooms_to_render(t_data s)
{
	t_vis_rooms	*vis_rooms;
	t_vis_rooms	*vis_room;
	t_room		*current_s_room;

	current_s_room = s.rooms;
	vis_rooms = make_new_vis_room();
	vis_room = vis_rooms;
	while (current_s_room)
	{
		color_and_coord(vis_room, current_s_room, s);
		if (current_s_room->next)
		{
			vis_room->next = make_new_vis_room();
			vis_room = vis_room->next;
		}
		current_s_room = current_s_room->next;
	}
	return (vis_rooms);
}

void			push_links_ro_render(t_data s, int i)
{
	t_vis_rooms	*vis_room;
	t_link		*norm_room;
	t_vis_rooms	*end_line;

	while (++i < s.links_count)
	{
		norm_room = s.links[i];
		vis_room = g_vis_rooms;
		while (vis_room && vis_room->num != i)
			vis_room = vis_room->next;
		if (vis_room)
			while (norm_room)
			{
				end_line = g_vis_rooms;
				while (end_line && end_line->num != norm_room->pair)
					end_line = end_line->next;
				SDL_SetRenderDrawColor(g_main_render, vis_room->r,
					vis_room->g, vis_room->b, 100);
				if (norm_room->pair >= i)
					SDL_RenderDrawLineF(g_main_render,
						vis_room->room.x + 25, vis_room->room.y + 25,
						end_line->room.x + 25, end_line->room.y + 25);
				norm_room = norm_room->next;
			}
	}
}

void			push_names_ro_render(t_data s)
{
	t_vis_rooms	*vis_room;
	t_room		*norm_room;
	TTF_Font	*courier;
	SDL_Rect	name_rect;

	vis_room = g_vis_rooms;
	norm_room = s.rooms;
	courier = TTF_OpenFont("Vizualize/InputMono-Regular.ttf", 20);
	if (courier == NULL)
		error("Font didn't find. SDL error: ", TTF_GetError());
	while (vis_room && norm_room)
	{
		if (vis_room->num == norm_room->n)
		{
			TTF_SizeText(courier, norm_room->name, &name_rect.w, &name_rect.h);
			name_rect.x = (int)vis_room->room.x;
			name_rect.y = (int)vis_room->room.y;
			SDL_RenderCopy(g_main_render,
				SDL_CreateTextureFromSurface(g_main_render,
				TTF_RenderText_Solid(courier, norm_room->name, BLACK)),
				NULL, &name_rect);
			vis_room = vis_room->next;
		}
		norm_room = norm_room->next;
	}
	TTF_CloseFont(courier);
}

void		push_ant_texture_to_render(SDL_FRect pos)
{
	SDL_Surface	*ant_surface;
	SDL_Texture	*ant_texture;
	SDL_FRect	ant_texture_settings;

	ant_surface = IMG_Load("Vizualize/ant.png");
	if (ant_surface == NULL)
		error("Ant picture could not load. SDL error: ", IMG_GetError());
	ant_texture = SDL_CreateTextureFromSurface(g_main_render, ant_surface);
	if (ant_texture == NULL)
		error("Ant texture could not build. SDL error: ", SDL_GetError());
	ant_texture_settings.h = 50;
	ant_texture_settings.w = 50;
	ant_texture_settings.x = pos.x;
	ant_texture_settings.y = pos.y;
	SDL_RenderCopyF(g_main_render, ant_texture, NULL, &ant_texture_settings);
}
