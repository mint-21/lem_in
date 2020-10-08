/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualise.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 13:42:35 by asmall            #+#    #+#             */
/*   Updated: 2020/09/18 13:42:38 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISE_H
# define VISUALISE_H

# include "/Users/vfearles/.brew/include/SDL2/SDL.h"
# include "/Users/vfearles/.brew/include/SDL2/SDL_ttf.h"
# include "/Users/vfearles/.brew/include/SDL2/SDL_image.h"

# include "../src/lemin.h"
# include <stdio.h>
# include <stdbool.h>
# include <time.h>

# define BLACK (SDL_Color){0, 0, 0, 255}
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_FPS 60
# define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

SDL_Window					*g_main_window;
SDL_Renderer				*g_main_render;
t_data						g_s;

typedef struct				s_vis_rooms
{
	SDL_FRect				room;
	struct s_vis_rooms		*next;
	char					*name;
	int						num;
	unsigned short int		r;
	unsigned short int		g;
	unsigned short int		b;
}							t_vis_rooms;

t_vis_rooms					*g_vis_rooms;

typedef struct				s_vis_ants
{
	char					*current_name;
	char					*next_name;
	SDL_FRect				current_room;
	SDL_FRect				next_room;
	float					x_diff;
	float					y_diff;
}							t_vis_ants;

typedef struct				s_turns
{
	char					**ant_and_room;
	struct s_turns			*next;
}							t_turns;

/*
** main.c
*/

void						error(const char *s, const char *t);
void						render_process(t_data s, t_vis_ants **array);
void						event_handler(t_data *g_s);

/*
** ft_ants_move.c
*/

void						start_process(t_vis_ants *array);

/*
** ft_render_info.c
*/

t_vis_rooms					*render_rooms(t_data s);
void						render_links(t_data s, int i);
void						render_name_room(t_data s);
void						render_texture_png(SDL_FRect pos);

/*
** ft_help_funct.c
*/

int							ft_find_max_x(t_data s);
int							ft_find_max_y(t_data s);
t_vis_rooms					*make_new_vis_room();
t_vis_ants					*make_new_vis_ants_array(t_data s);
void						null_ptr_ant(t_vis_ants *ant, int *null_count);

/*
** ft_push_turns.c
*/

bool						parse_turns_line(t_vis_ants **array, t_data **g_s);

/*
** ft_render_init.c
*/

int							init_sdl(void);
int							close_sdl(void);
void						color_and_coord(t_vis_rooms *vis_room,
								t_room *current_s_room, t_data s);

#endif
