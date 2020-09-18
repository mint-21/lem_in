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

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>

# define E_MALLOC 1
# define E_NO_CORRECT 2
# define E_START 3
# define E_END 4
# define E_ANT 5
# define E_INT 6
# define E_CONNECT 7
# define E_PATH 8
# define E_HASH 9
# define E_ROOM 10
# define E_COORD 12

# define INF		(0x7FFFFFFF)
# define BUFF_SIZE	2048

# define MAX(a, b) (a > b ? a : b)
# define MIN(a, b) (a < b ? a : b)

# define MAX_INT				2147483647

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

typedef struct		s_connect
{
	int				weight;
	struct s_room	*room_one;
	struct s_room	*room;
	struct s_connect	*next;
	struct s_connect	*prev;
	struct s_connect	*turn_next;
	struct s_connect	*parrent;
}					t_connect;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				n;
	t_connect			*connects;
	int				connects_count;
	struct s_room	*out_part;
	struct s_room	*in_part;
	struct s_room	*room_par;
	int				ant;
	int				weight;
	struct s_room	*next;
	int				state;
}					t_room;

typedef struct			s_link
{
	int					pair;
	int					mark;
	struct s_link		*next;
}						t_link;

typedef struct		s_valid
{
	int				li_room_begin;
	int				li_room_finish;
	int				li_connects_bigin;
	int				li_connects_finish;
	int				hash_start;
	int				hash_end;
	int				valid_flag;
}					t_valid;

/*
** ways_dij: все пути которые находил алгоритм дейкстры.
** hash_start: index of room start; hash_end: index of room end.
** options: варианты выбранных путей; best_opt: лучшие варианты.
*/

typedef struct		s_data
{
	int				ants;
	int				step;
	int				flag;
	int				rooms_count;
	int				total_ways;
	int				links_count;
	char			*map_data;
	char			**split;
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	t_option		*options;
	t_option		*best_opt;
	t_way			*ways_dij;
	t_flags			flags;
	t_valid			check;
	t_link			**links;
}					t_data;

t_data	ft_zerodata(void);
int	add_link(t_data *s, char *tab);
void				ft_flags_lemin(t_flags *flags, int ac, char **av);
char				*ft_lemin_read(t_flags *flags, char ***str_split);
int					ft_correct(t_data *data, t_valid *check, char **strings);
int					ft_correct_hash(t_valid *check, char *str);
int					ft_correct_ants(char *str, t_data *data);
int					ft_correct_rooms(char *str, t_valid *check, int j);
int					ft_correct_rooms_double(char *room1, char *room2);
void				ft_correct_connects(char *str, t_valid *check, int j);
//int					ft_parse_data(t_data *data, t_valid *check, char **str);
void				ft_rooms(t_data *data, char *str);
t_room				*ft_createroom(char *line);
void				ft_connects(t_data *data, char *str);
t_connect				*ft_createconnect(t_room *room);
int					ft_findrooms(t_data *data, char *connect, t_room **room1,
					t_room **room2);
void				ft_find_all_ways(t_data *data);
int					ft_suurballe(t_data *data);
void				djkastra(int flag, t_data *data);
// void				ft_turn(t_room *room, t_room *start, int *flag);
void				ft_change_ribs(t_path *path);
void				ft_lemin(t_data *data);
void				*ft_free_str_split(char **str_split);
void				ft_free_data(t_data *data);
void				ft_print_error(int id);
void				ft_perror();
int					ft_atoi_mod(const char *str);
int					steps_for_ants(t_way *way, int ants);
void				find_of_ways_struct(t_data *data);
void  				ft_find_null(t_path *path);
void				null_turn(t_connect *reverse_h, t_connect *reverse_t, t_room *end);
void				ft_redirection_connect(t_room *src, t_room *dst, t_connect *connect);
void				redirection_conditions(t_connect *connect, t_room *src);
void				create_out_room(t_room *in, t_room *out, t_room *room, t_connect *connect);
void   				ft_creat_duplicate(t_path *path, t_room *in);
void				create_out_in_room(t_room *in, t_room *out);
t_room				*ft_create_new_room(char *line);
int					check_double_coor(t_data *s, t_room *curr, char *str);
void				ft_step(t_data *data, int *ant, t_buf *buf, int steps);
void				copy_text_buff(t_data *data, t_path *path, t_buf *buf, int ant);
t_way 				*way_init(t_way *way, t_path *path, int weight, t_way *ways);
t_connect			*create_inhead(t_path *tmp, t_path *path, t_connect *head, int *weight);
t_connect			*terms(t_connect *head, t_connect *connect);
void				path_init(t_path *path, t_room *end, t_path *tmp);
t_connect 			*turn_room(t_room *room, t_connect *connect, t_room *start, int *flag);
int					ft_init_path_struct(t_path *path, t_room *room, int path_cost);
void				path(t_room *room, t_room *start, t_way **ways, int path_cost);
void				init_way(t_way *way, int path_cost, t_way **ways, t_path *path);
void				ft_print_ways(t_way *way, int steps);
void				print_n_free_map_data(char **map_data);

#endif
