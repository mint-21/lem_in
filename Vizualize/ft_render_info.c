/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:33:25 by asmall            #+#    #+#             */
/*   Updated: 2020/09/22 12:06:15 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

void			create_name_room(t_vis_rooms *vis_room, t_room *norm_room,
					TTF_Font *courier)
{
	SDL_Rect	name_rect;

	TTF_SizeText(courier, norm_room->name, &name_rect.w, &name_rect.h);
	name_rect.x = (int)vis_room->room.x;
	name_rect.y = (int)vis_room->room.y;
	SDL_RenderCopy(g_main_render,
		SDL_CreateTextureFromSurface(g_main_render,
		TTF_RenderText_Solid(courier, norm_room->name, BLACK)),
		NULL, &name_rect);
}

void			render_name_room(t_data s)
{
	t_vis_rooms	*vis_room;
	t_room		*norm_room;
	TTF_Font	*courier;

	courier = NULL;
	vis_room = g_vis_rooms;
	norm_room = s.rooms;
	courier = TTF_OpenFont("Vizualize/resourse/InputMono-Regular.ttf", 20);
	if (courier == NULL)
		error("Font didn't find. SDL error: ", TTF_GetError());
	while (vis_room && norm_room)
	{
		if (vis_room->num == norm_room->n)
		{
			create_name_room(vis_room, norm_room, courier);
			vis_room = vis_room->next;
		}
		norm_room = norm_room->next;
	}
	TTF_CloseFont(courier);
}

t_vis_rooms		*render_rooms(t_data s)
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

void			render_links(t_data s, int i)
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

void			render_texture_png(SDL_FRect pos)
{
	SDL_Surface	*ant_surface;
	SDL_Texture	*ant_texture;
	SDL_FRect	ant_texture_settings;

	ant_surface = IMG_Load("Vizualize/resourse/man_ant.png");
	if (ant_surface == NULL)
		error("Ant picture could not load. SDL error: ", IMG_GetError());
	ant_texture = SDL_CreateTextureFromSurface(g_main_render, ant_surface);
	if (ant_texture == NULL)
		error("Ant texture could not build. SDL error: ", SDL_GetError());
	ant_texture_settings.h = 75;
	ant_texture_settings.w = 75;
	ant_texture_settings.x = pos.x;
	ant_texture_settings.y = pos.y;
	SDL_RenderCopyF(g_main_render, ant_texture, NULL, &ant_texture_settings);
}