/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:33:25 by asmall            #+#    #+#             */
/*   Updated: 2021/05/07 14:02:12 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

void	render_name_room(t_data s)
{
	t_room_v	*vis_room;
	t_room		*norm_room;
	TTF_Font	*courier;

	courier = NULL;
	vis_room = g_vis_rooms;
	norm_room = s.rooms;
	courier = TTF_OpenFont("vis/resourse/InputMono-Regular.ttf", 20);
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

t_room_v	*render_rooms(t_data s)
{
	t_room_v	*vis_rooms;
	t_room_v	*vis_room;
	t_room		*current_s_room;

	current_s_room = s.rooms;
	vis_rooms = init_vis_room();
	vis_room = vis_rooms;
	while (current_s_room)
	{
		color_and_coord(vis_room, current_s_room, s);
		if (current_s_room->next)
		{
			vis_room->next = init_vis_room();
			vis_room = vis_room->next;
		}
		current_s_room = current_s_room->next;
	}
	return (vis_rooms);
}

void	render_links_help(t_room_v *vis_room, t_link *norm_room, int i)
{
	t_room_v	*end_line;

	end_line = g_vis_rooms;
	while (end_line && end_line->num != norm_room->pair)
		end_line = end_line->next;
	SDL_SetRenderDrawColor(g_main_render, vis_room->r,
		vis_room->g, vis_room->b, 100);
	if (norm_room->pair >= i)
		SDL_RenderDrawLineF(g_main_render,
			vis_room->room.x + 25, vis_room->room.y + 25,
			end_line->room.x + 25, end_line->room.y + 25);
}

void	render_links(t_data s, int i)
{
	t_room_v	*vis_room;
	t_link		*norm_room;

	while (++i < s.check.li_connects_finish)
	{
		printf("\n ________%i______", s.links_count);
		norm_room = s.links[i];
		vis_room = g_vis_rooms;
		while (vis_room && vis_room->num != i)
			vis_room = vis_room->next;
		if (vis_room)
		{
			while (norm_room)
			{
				render_links_help(vis_room, norm_room, i);
				norm_room = norm_room->next;
			}
		}
	}
}

void	render_texture_png(SDL_FRect pos)
{
	SDL_Surface	*ant_surface;
	SDL_Texture	*ant_texture;
	SDL_FRect	texture_settings;

	ant_surface = IMG_Load("vis/resourse/man_ant.png");
	if (ant_surface == NULL)
		error("Ant picture could not load. SDL error: ", IMG_GetError());
	ant_texture = SDL_CreateTextureFromSurface(g_main_render, ant_surface);
	if (ant_texture == NULL)
		error("Ant texture could not build. SDL error: ", SDL_GetError());
	texture_settings.h = 75;
	texture_settings.w = 75;
	texture_settings.x = pos.x;
	texture_settings.y = pos.y;
	SDL_RenderCopyF(g_main_render, ant_texture, NULL, &texture_settings);
}
