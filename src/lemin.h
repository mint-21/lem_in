/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:31:10 by asmall            #+#    #+#             */
/*   Updated: 2020/09/13 15:05:41 by vfearles         ###   ########.fr       */
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
# define E_CONNECT 6
# define E_PATH 7
# define E_HASH 8
# define E_ROOM 9
# define E_COORD 10

# define INF		10000000
# define BUFF_SIZE	2048

# define MAX(a, b) (a > b ? a : b)
# define MIN(a, b) (a < b ? a : b)

# define MAX_INT	2147483647

typedef struct			s_buf
{
	char				str[BUFF_SIZE];
	size_t				i;
	int					space;
}						t_buf;

/*
** t_path: list of rooms
*/

typedef struct			s_path
{
	struct s_room		*room;
	struct s_path		*next;
	struct s_path		*prev;
}						t_path;

typedef struct			s_ants
{
    int					num;
    t_path				*curr;
    struct s_ants		*next;
}						t_ants;

/*
** t_way: list of paths (from rooms)
*/

typedef struct			s_way
{
	struct s_path		*path;
    t_ants *last_ant;
	int					len;
	int					ants;
	struct s_way		*next;
	struct s_way		*prev;
	t_ants *buf;
}						t_way;

/*
** s_option: path variant structure.
*/

typedef struct			s_option
{
	t_way				*ways;
	int					steps;
	struct s_option		*next;
}						t_option;

typedef struct			s_connect
{
	int					weight;
	struct s_room		*room_one;
	struct s_room		*room;
	struct s_connect	*next;
	struct s_connect	*prev;
	struct s_connect	*turn_next;
	struct s_connect	*parrent;
}						t_connect;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					n;
	t_connect			*connects;
	int					connects_count;
	struct s_room		*out_part;
	struct s_room		*in_part;
	struct s_room		*room_par;
	int					ant;
	int					weight;
	struct s_room		*next;
	int					state;
}						t_room;

typedef	struct			s_rooms
{
    t_room				*r;
    struct s_rooms		*next;
    struct s_rooms		*prev;
}						t_rooms;

typedef struct			s_link
{
	int					pair;
	int					mark;
	struct s_link		*next;
}						t_link;

typedef struct			s_valid
{
	int					li_room_begin;
	int					li_room_finish;
	int					li_connects_bigin;
	int					li_connects_finish;
	int					hash_start;
	int					hash_end;
	int					valid_flag;
}						t_valid;

/*
** ways_dij: all the paths that Dijkstra's algorithm found.
** hash_start: index of room start; hash_end: index of room end.
** options: options for selected paths; best_opt: the best options.
*/

typedef struct			s_data
{
	int					ants;
	int					step;
	int					flag;
	int					rooms_count;
	int					total_ways;
	int					links_count;
	char				*map_data;
	char				**split;
	t_room				*start;
	t_room				*end;
	t_room				*rooms;
	t_option			*options;
	t_option			*best_opt;
	t_way				*ways;
	t_valid				check;
	t_link				**links;
	int					vis_quit;
	int					vis_pause;
	int					ant;
	int					steps;
}						t_data;

t_data					ft_zerodata(void);
int						add_link(t_data *s, char *tab);
char					*reading_card(char ***str_split, int fd);
int						ft_correct(t_data *data, t_valid *check,
									char **strings);
int						ft_correct_hash(t_valid *check, char *str);
void					terms_connect(t_room *room_one, t_connect *connect);
int						ft_correct_ants(char *str, t_data *data);
int						ft_correct_rooms(char *str, t_valid *check, int j);


void					ft_correct_connects(char *str, t_valid *check, int j);
t_room					*ft_initialization_struct_room(char *line);
void					ft_connects(t_data *data, char *str);
t_connect				*ft_createconnect(t_room *room);
int						ft_srb_alg(t_data *data);
void					djkastra(int flag, t_data *data, int room_count);
void					ft_change_ribs(t_path *path);
void					ft_buff_lem(t_data *data);
void					ft_struct_free(t_data *data);
void					ft_print_error(int id);
void					ft_perror();
int						steps_for_ants(t_way *way, int ants, int steps);
void					find_of_ways_struct(t_data *data);
void					ft_find_null(t_path *path);
void					null_turn(t_connect *reverse_h, t_connect *reverse_t,
								t_room *end);
void					ft_redirection_connect(t_room *src, t_room *dst,
											t_connect *connect);
void					redirection_conditions(t_connect *connect, t_room *src);
void					create_out_room(t_room *in, t_room *out, t_room *room,
										t_connect *connect);
void					ft_creat_duplicate(t_path *path, t_room *in);
void					create_out_in_room(t_room *in, t_room *out);

int						check_double_coor(t_data *s, t_room *curr, char *str);


t_way					*way_init(t_way *way, t_path *path, int weight,
								t_way *ways);
t_connect				*create_inhead(t_path *tmp, t_path *path,
										t_connect *head, int *weight);
t_connect				*terms(t_connect *head, t_connect *connect);
void					path_init(t_path *path, t_room *end, t_path *tmp);
t_connect				*turn_and_change(t_room *room, t_connect *connect,
									t_room *start, int *flag);
int						ft_init_path_struct(t_path *path, t_room *room,
											int path_cost);
void					path(t_room *room, t_room *start, t_way **ways,
							int path_cost);
void					init_way(t_way *way, int path_cost, t_way **ways,
								t_path *path);

void					print_n_free_map_data(char **map_data);
void					terms_null(t_room *room);
void					ft_clean_links(t_data *s);
int						ft_check_room_link(t_data *data, char *connect_str,
							t_room **room1, t_room **room2);


//новое
int count_link(t_room *room);
int get_max_path(t_room *start, t_room *end);
void	free_path_list(t_way *l);
void	free_path(t_path *p);
void suurb(t_data *data);
void split(t_way *way);
t_path *bfs(t_data *data);
t_path *assemble_path(t_room *end, t_room *start);
void q_add_link(t_rooms **q, t_connect *l, t_room *par);
void merge(t_way *way);
t_rooms *add_to_buf(t_room *r, t_rooms *buf);
void free_links(t_connect *l);
t_connect *del_zero_link(t_connect *l);
void free_buf(t_rooms *buf);
int collision_handle(t_way *list, t_path *p, int ret);
void recount_len(t_way *l);
t_connect *del_link(t_connect *l, t_room *r);
void modify_data(t_path *p);
t_way *check_steps(t_way *p_list, t_way *final, int ants);
void free_path_list(t_way *l);
void free_path(t_path *p);
t_way *lst_copy(t_way *l);
void bubble_sort(t_way *l);
void restore(t_data *data, t_way *p_list);
void	fill_buf(t_way *l);
int		print_line(t_way *l, int step);
t_ants	*buf_delete_ant(t_ants **buf, t_ants *ant);


#endif
