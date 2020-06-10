/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:31:10 by vfearles          #+#    #+#             */
/*   Updated: 2020/05/13 15:05:41 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

# define E_MALLOC 1
# define E_NO_correct 2
# define E_START 3
# define E_END 4
# define E_ANT 5
# define E_INT 6
# define E_LINK 7
# define E_PATH 8
# define E_HASH 9
# define E_ROOM 10
# define E_COORD 12

# define INF		(0x7FFFFFFF)
# define BUFF_SIZE	2048

typedef struct		s_buf
{
	char			str[BUFF_SIZE];
	size_t			i;
	int				space;
}					t_buf;

typedef struct		s_flags
{
	char			*fd_path;
	char			ways;
}					t_flags;

/*
** t_path: список комнат
*/

typedef struct		s_path
{
	struct s_room	*room;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

/*
** t_way: список путей (из комнат)
*/

typedef struct		s_way
{
	struct s_path	*path;
	int				path_number;
	int				path_cost;
	int				ants;
	struct s_way	*next;
	struct s_way	*prev;
}					t_way;

/*
** s_option: структура варианта пути.
*/

typedef struct		s_option
{
	t_way			*ways;
	int				steps;
	struct s_option	*next;
}					t_option;

typedef struct		s_link
{
	int				weight;
	struct s_room	*room_one;
	struct s_room	*room;
	struct s_link	*next;
	struct s_link	*prev;
	struct s_link	*turn_next;
	struct s_link	*parrent;
}					t_link;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	t_link			*links;
	int				links_count;
	struct s_room	*room_out;
	struct s_room	*room_in;
	struct s_room	*room_par;
	int				ant;
	int				weight;
	struct s_room	*next;
	int				state;
}					t_room;

/*
** ways_dij: все пути которые находил алгоритм дейкстры.
** i_rooms_start: index where rooms begin.
** i_rooms_end: index where roms end.
** i_start: index of room start; i_end: index of room end.
** options: варианты выбранных путей; best_opt: лучшие варианты.
*/

typedef struct		s_data
{
	int				ants;
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	int				rooms_count;
	t_option		*options;
	t_option		*best_opt;
	t_way			*ways_dij;
	int				total_ways;
	int				i_rooms_start;
	int				i_rooms_end;
	int				i_links_start;
	int				i_links_end;
	int				i_start;
	int				i_end;
	int				v_flag;
	t_flags			flags;
}					t_data;

void				ft_flags_lemin(t_flags *flags, int ac, char **av);
char				*ft_lemin_read(t_flags *flags, char ***str_split);
int					ft_correct(t_data *data, char **strings);
int					ft_correct_hash(t_data *data, char *str);
int					ft_correct_ants(char *str, t_data *data);
int					ft_correct_rooms(char *str, t_data *data, int j);
void				ft_correct_links(char *str, t_data *data, int j);
int					ft_correct_duplicates_rooms(t_data *data, char **strings);
int					ft_parse_data(t_data *data, char **str_split);
void				ft_rooms(t_data *data, char *str);
t_room				*ft_createroom(char *line);
void				ft_links(t_data *data, char *str);
t_link				*ft_createlink(t_room *room);
int					ft_findrooms(t_data *data, char *link, t_room **room1,
					t_room **room2);
void				ft_find_all_ways(t_data *data);
int					ft_suurballe(t_data *data);
int					ft_ford(t_data *data);
void				ft_turn(t_room *room, t_room *start, int *flag);
void				ft_direction(t_path *path);
t_way				*ft_paths_ascending(t_room *start, t_room *end);
t_way				*ft_ways_ascending(t_link *turn_head, t_link *turn_tail,
					t_room *start, t_room *end);
void				ft_lemin(t_data *data);
void				*ft_free_str_split(char **str_split);
void				ft_free_data(t_data *data);
void				ft_print_error(int id);
void				ft_perror();
int					ft_atoi_mod(const char *str);
int					ft_min_steps_for_ants(t_way *way, int ants);
void				find_of_ways_struct(t_data *data);
void				init_var(t_option *var, t_way *new_ways, int new_steps);

#endif
