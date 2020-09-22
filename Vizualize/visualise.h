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

# include "/Users/asmall/.brew/include/SDL2/SDL.h"
# include "/Users/asmall/.brew/include/SDL2/SDL_ttf.h"
# include "/Users/asmall/.brew/include/SDL2/SDL_image.h"

# include "../src/lemin.h"
# include <stdio.h>
# include <stdbool.h>
# include <time.h>

# define OK 0
# define ERR -1
# define STOP -2

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
	char					*current_room_name;
	char					*next_room_name;
	SDL_FRect				current_room;
	SDL_FRect				next_room;
	float					x_diff;
	float					y_diff;
}							t_vis_ants;

typedef struct				s_turns_parser
{
	char					**ant_and_room;
	struct s_turns_parser	*next;
}							t_turns_parser;

/*
** main.c
*/

void						error(const char *s, const char *t);
void						push_all_to_render(t_data s, t_vis_ants **array);
void						event_handler(t_data *g_s);

/*
** ants_move.c
*/

int							if_turn_over(t_vis_ants **array, t_data *g_s);
void						print_ants(t_vis_ants *array);

t_vis_rooms					*push_rooms_to_render(t_data s);
void						push_links_ro_render(t_data s, int i);
void						push_names_ro_render(t_data s);
void						push_ant_texture_to_render(SDL_FRect pos);

t_vis_rooms					*make_new_vis_room();
int							ft_find_max_x(t_data s);
int							ft_find_max_y(t_data s);
int							close_all(void);
void						null_ptr_ant(t_vis_ants *ant, int *null_count);

bool						parse_turns_line(t_vis_ants **array, t_data **g_s);
t_turns_parser				*make_new_ant_turn(void);
t_vis_ants					*make_new_vis_ants_array(t_data s);


void						start_process(t_vis_ants *array);

bool						init(void);

#endif
