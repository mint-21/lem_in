/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualise.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 13:42:35 by asmall            #+#    #+#             */
/*   Updated: 2021/05/07 16:03:40 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISE_H
# define VISUALISE_H

# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"

# include "../src/lemin.h"
# include <stdio.h>
# include <stdbool.h>

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define STEP_SCREEN 60
# define SCREEN_TICKS_PER_FRAME 16

SDL_Window					*g_main_window;
SDL_Renderer				*g_main_render;
t_data						g_struct;

typedef struct s_room_v
{
	SDL_FRect				room;
	struct s_room_v			*next;
	char					*name;
	int						num;
	unsigned short int		r;
	unsigned short int		g;
	unsigned short int		b;
}							t_room_v;

t_room_v					*g_vis_rooms;

typedef struct s_ants_v
{
	char					*curr_name;
	char					*next_name;
	SDL_FRect				curr_room;
	SDL_FRect				next_room;
	float					x_diff;
	float					y_diff;
}							t_ants_v;

typedef struct s_turns
{
	char					**room_ant;
	struct s_turns			*next;
}							t_turns;

/*
** main.c
*/

void						error(const char *s, const char *t);
void						render_process(t_data s, t_ants_v **array);
void						event_handler(t_data *g_struct);

/*
** ft_ants_move.c
*/

void						start_process(t_ants_v *array);

/*
** ft_render_info.c
*/

t_room_v					*render_rooms(t_data s);
void						render_links(t_data s, int i);
void						render_name_room(t_data s);
void						render_texture_png(SDL_FRect pos);

/*
** ft_help_funct.c
*/

int							ft_max(int a, int b);
int							calc_max_xy(t_data s, int flag);
t_room_v					*init_vis_room(void);
t_ants_v					*array_vis_ants(t_data s);
void						ant_on_null(t_ants_v *ant, int *null_count);
void						create_name_room(t_room_v *vis_room,
								t_room *norm_room, TTF_Font *courier);

/*
** ft_push_turns.c
*/

bool						turn_line(t_ants_v **array, t_data **g_struct);

/*
** ft_render_init.c
*/

int							init_sdl(void);
int							close_sdl(void);
void						color_and_coord(t_room_v *vis_room,
								t_room *current_s_room, t_data s);

#endif
