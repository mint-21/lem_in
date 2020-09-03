/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:14:27 by asmall            #+#    #+#             */
/*   Updated: 2019/10/20 16:58:08 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

bool		init(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. SDL error: %s\n", SDL_GetError());
		return (false);
	}
	g_main_window = SDL_CreateWindow("Lem_in", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_main_window == NULL)
	{
		printf("SDL could not create window. SDL error: %s\n", SDL_GetError());
		return (false);
	}
	g_main_render = SDL_CreateRenderer(g_main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(g_main_render == NULL )
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return (false);
	}
	int	imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image couldn't initialize. SDL error: %s\n", IMG_GetError());
		return (false);
	}
	if (TTF_Init() < 0)
	{
		printf("SDL_ttf couldn't initialize. SDL error: %s\n", TTF_GetError());
		return (false);
	}
	return (true);
}

/*
**			Makes rooms in window
*/
t_vis_rooms		*push_rooms_to_render(t_data s)
{
	t_vis_rooms	*vis_rooms;
	t_vis_rooms	*current_vis_room;
	t_room		*current_s_room = s.room;

	vis_rooms = make_new_vis_room();
	current_vis_room = vis_rooms;
	while (current_s_room)
	{
		current_vis_room->room.x = ft_abs(current_s_room->x * (SCREEN_WIDTH / (MAX(ft_find_max_x(s), 1))) - 50);
		current_vis_room->room.y = ft_abs(current_s_room->y * (SCREEN_HEIGHT / (MAX(ft_find_max_y(s), 1))) - 50);
		current_vis_room->name = current_s_room->name;
		current_vis_room->num = current_s_room->n;
		current_vis_room->r = rand() % 255 + 1;
		current_vis_room->g = rand() % 255 + 1;
		current_vis_room->b = rand() & 255 + 1;
		SDL_SetRenderDrawColor(g_main_render, current_vis_room->r, current_vis_room->g, current_vis_room->b, 100);
	//убрать дебаг!
		if (g_debug)
			printf("Name = %s, x = %f, y = %f, RGB = %d %d %d\n",
					current_vis_room->name, current_vis_room->room.x,
					current_vis_room->room.y,
					current_vis_room->r, current_vis_room->g,
					current_vis_room->b);
		SDL_RenderFillRectF(g_main_render, &current_vis_room->room);
		if (current_s_room->next)
		{
			current_vis_room->next = make_new_vis_room();
			current_vis_room = current_vis_room->next;
		}
		current_s_room = current_s_room->next;
	}
	return (vis_rooms);
}

void		push_links_ro_render(t_data s)
{
	t_vis_rooms	*current_vis_room;
	t_link		*current_usual_room;
	t_vis_rooms	*end_of_line;

	for (int i = 0; i < s.n_links; i++)
	{
		current_usual_room = s.links[i];
		current_vis_room = g_vis_rooms;
		while (current_vis_room && current_vis_room->num != i)
			current_vis_room = current_vis_room->next;
		if (current_vis_room)
			while (current_usual_room)
			{
				end_of_line = g_vis_rooms;
				while (end_of_line && end_of_line->num != current_usual_room->pair)
					end_of_line = end_of_line->next;
				SDL_SetRenderDrawColor(g_main_render, current_vis_room->r, current_vis_room->g, current_vis_room->b, 100);
				if (current_usual_room->pair >= i)
					SDL_RenderDrawLineF(g_main_render,
										current_vis_room->room.x + 25,
										current_vis_room->room.y + 25,
										end_of_line->room.x + 25,
										end_of_line->room.y + 25);
				current_usual_room = current_usual_room->next;
			}
	}
}

void		push_names_ro_render(t_data s)
{
	t_vis_rooms	*current_vis_room = g_vis_rooms;
	t_room		*current_usual_room = s.room;
	TTF_Font	*Courier = NULL;
	SDL_Color	Black = {0, 0, 0, 255};
	SDL_Rect	name_rect;

	Courier = TTF_OpenFont("Vizualize/IMG/Courier New.ttf", 30);
	if (Courier == NULL)
	{
		printf("Font didn't find. SDL error: %s\n", TTF_GetError());
		return ;
	}
	while (current_vis_room && current_usual_room)
	{
		if (current_vis_room->num == current_usual_room->n)
		{
			TTF_SizeText(Courier, current_usual_room->name, &name_rect.w, &name_rect.h);
			name_rect.x = (int)current_vis_room->room.x;
			name_rect.y = (int)current_vis_room->room.y;
			SDL_RenderCopy(g_main_render, SDL_CreateTextureFromSurface(g_main_render, TTF_RenderText_Solid(Courier, current_usual_room->name, Black)), NULL, &name_rect);
			current_vis_room = current_vis_room->next;
		}
		current_usual_room = current_usual_room->next;
	}
}

void		push_ant_texture_to_render(SDL_FRect pos)
{
	SDL_Surface	*ant_surface;
	SDL_Texture	*ant_texture;
	SDL_FRect	ant_texture_settings;

	ant_surface = IMG_Load("Vizualize/IMG/ant.png");
	if (ant_surface == NULL)
	{
		printf("Ant picture could not load. SDL error: %s\n", IMG_GetError());
		return ;
	}
	ant_texture = SDL_CreateTextureFromSurface(g_main_render, ant_surface);
	if (ant_texture == NULL)
	{
		printf("Ant texture could not build. SDL error: %s\n", SDL_GetError());
		return ;
	}
	ant_texture_settings.h = 50;
	ant_texture_settings.w = 50;
	ant_texture_settings.x = pos.x;
	ant_texture_settings.y = pos.y;
	SDL_RenderCopyF(g_main_render, ant_texture, NULL, &ant_texture_settings);
}
