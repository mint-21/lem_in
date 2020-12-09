/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:28:23 by asmall            #+#    #+#             */
/*   Updated: 2020/06/13 19:28:53 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** reading_card: reading the map. ft_correct: card validation
** ft_find_all_ways: the main algorithm of the program
** print_n_free_map_data: printing the map to the console
** ft_buff_lem: output to the console of the program's response
*/

void	set_distance(t_room *rooms)
{
	while (rooms)
	{
		rooms->weight = INF;
		rooms = rooms->next;
	}
}

void q_insert(t_rooms *q, t_rooms *new) {
    while (q->next && q->r->weight <= new->r->weight)
        q = q->next;
    if (!q->next && q->r->weight <= new->r->weight) {
        q->next = new;
        new->prev = q;
    } else {
        if (q->prev)
            q->prev->next = new;
        new->prev = q->prev;
        new->next = q;
        q->prev = new;
    }
}

void q_add_room(t_rooms **q, t_room *r)
{
    t_rooms *new;

    if (!(new = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
        exit(1);
    new->r = r;
    if (!*q || r->weight < (*q)->r->weight) {
        if (*q)
            (*q)->prev = new;
        new->next = *q;
        *q = new;
    } else
        q_insert(*q, new);
}

void q_add_link(t_rooms **q, t_connect *l, t_room *par)
{
    while (l)
    {
        if (l->room->weight == INF)
        {
            l->room->weight = par->weight + l->weight;
            l->room->room_par = par;
            q_add_room(q, l->room);
        }
        l = l->next;
    }
}

t_room *q_get(t_rooms **q)
{
    t_room *ret;

    if (!*q)
        return (NULL);
    ret = (*q)->r;
    *q = (*q)->next;
    return (ret);
}

void q_free(t_rooms *q)
{
    if (!q)
        return;
    q_free(q->next);
    free(q);
}

t_path *p_push_begin(t_room *r, t_path *p)
{
    t_path *new;

    if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
        exit(1);
    new->room = r;
    new->next = p;
    if (p)
        p->prev = new;
    return (new);
}

t_path *assemble_path(t_room *end, t_room *start)
{
    t_path *p;
    int len;

    p = NULL;
    len = 0;
    while (end != start)
    {
        p = p_push_begin(end, p);
        end = end->room_par;
        len++;
    }
    p = p_push_begin(start, p);
    return (p);
}

t_path *bfs(t_data *data)
{
    t_room *w;
    t_rooms *q;

    w = data->start;
    q = NULL;
    q_add_link(&q, w->connects, w);
    if (!(w = q_get(&q)))
        return (NULL);
    while (w != data->end)
    {
        q_add_link(&q, w->connects, w);
        if (!(w = q_get(&q)))
            return (NULL);
    }
    q_free(q);
    return (assemble_path(w, data->start));
}

int p_len(t_path *p)
{
    int len;

    len = 0;
    while (p)
    {
        p = p->next;
        len++;
    }
    return (len);
}

t_way *plist_push_back(t_way *way, t_path *p)
{
    t_way *first;
    t_way *new;

    first = way;
    if (!(new = (t_way *)ft_memalloc(sizeof(t_way))))
        exit(1);
    new->len = p_len(p);
    new->path = p;
    if (!first)
        return (new);
    while (way->next)
        way = way->next;
    way->next = new;
    new->prev = way;
    return (first);
}

void free_links(t_connect *l)
{
    if (!l)
        return;
    free_links(l->next);
    free(l->next);
    free(l);
}

void free_path(t_path *p)
{
    if (!p)
        return;
    free_path(p->next);
    free(p);
}

void free_path_list(t_way *l)
{
    if (!l)
        return;
    free_path_list(l->next);
    free_path(l->path);
    free(l);
}

t_connect *del_zero_link(t_connect *l)
{
    t_connect *f;
    t_connect *prev;

    f = l;
    prev = NULL;
    while (l)
    {
        if (l->weight == 0)
        {
            if (!prev)
                f = l->next;
            else
                prev->next = l->next;
            free(l);
            break;
        }
        l = l->next;
        prev = l;
    }
    return (f);
}

t_room *b_find(t_room *r, t_room *buf)
{
    while (buf)
    {
        if (buf == r)
            break;
        buf = buf->next;
    }
    return (buf);
}

t_room *add_to_buf(t_room *r, t_room *buf)
{
    t_room *new;

    if (b_find(r, buf))
        return (buf);
    if (!(new = (t_room *)ft_memalloc(sizeof(t_room))))
        exit(1);
    new->next = buf;
    new = r;
    return (new);
}

void merge_vertex(t_path *vert, t_room **buf)
{
    if (vert->room->out_part)
    {
        free_links(vert->room->connects);
        vert->room->out_part->connects = del_zero_link(vert->room->out_part->connects);
        vert->room->connects = vert->room->out_part->connects;
    }
    else if (vert->room->in_part)
    {
        vert->room = vert->room->in_part;
        if (vert->room == vert->next->room)
        {
            vert->next = vert->next->next;
            free(vert->next->prev);
            if (vert->next)
                vert->next->prev = vert;
        }
    }
    *buf = add_to_buf(vert->room->out_part, *buf);
    vert->room->in_part = NULL;
    vert->room->out_part = NULL;
}

void free_buf(t_room *buf)
{
    if (!buf)
        return;
    free_buf(buf->next);
    free(buf);
}

void merge(t_way *way)
{
    t_path *p;
    t_room *buf;

    buf = NULL;
    if (!way)
        return;
    while (way)
    {
        p = way->path->next;
        while (p->next)
        {
            merge_vertex(p, &buf);
            p = p->next;
        }
        way = way->next;
    }
    free_buf(buf);
}

t_path *get_first(t_path *p)
{
    while (p->prev)
        p = p->prev;
    return (p);
}

void restore_col(t_path *start, t_path *end)
{
    if (start == end)
        return;
    restore_col(start->next, end);
    free(start);
}

t_path *remove_collision(t_path *col_start1, t_path *col_end2)
{
   t_path *col_start2;
   t_path *col_end1;

   col_start2 = col_end2;
   col_end1 = col_start1;
   while (col_start2->prev->room == col_end1->next->room)
   {
       col_start2 = col_start2->prev;
       col_end1 = col_end1->next;
   }
   restore_col(col_start1->next, col_end1);
   restore_col(col_start2->next, col_end2);
   col_start1->next = col_end2->next;
   col_start1->next->prev = col_start1;
   col_start2->next = col_end1->next;
   col_start2->next->prev = col_start2;
   free(col_end1);
   free(col_end2);
   return (col_start2);
}

t_path *find_room(t_way *l, t_room *tofind, t_path *ap)
{
    t_path *tmp;

    while (l)
    {
        if (l->path != ap)
        {
            tmp = l->path;
            while (tmp)
            {
                if (tmp->room == tofind)
                    return (tmp);
                tmp = tmp->next;
            }
        }
        l = l->next;
    }
    return (NULL);
}

int collision_handle(t_way *list, t_path *p, int ret)
{
    t_path *tmp;
    t_path *first;

    first = get_first(p);
    while (p->next)
    {
        if ((tmp = find_room(list, p->room, first)))
        {
            ret = 1;
            p = remove_collision(p, tmp);
            first = get_first(p);
        } else
            p = p->next;
    }
    return (ret);
}

void recount_len(t_way *l)
{
    while (l)
    {
        l->len = p_len(l->path);
        l = l->next;
    }
}

t_connect *del_link2(t_connect *l, t_room *r)
{
    t_connect *prev;
    t_connect *first;

    prev = NULL;
    first = l;
    while (l)
    {
        if (l->room == r)
        {
            if (prev)
                prev->next = l->next;
            else
                first = first->next;
            free(l);
            break;
        }
        prev = l;
        l = l->next;
    }
    return (first);
}

t_connect *del_link(t_connect *l, t_room *r)
{
    if (!l)
        return (NULL);
    if (!l->next)
    {
        free(l);
        return (NULL);
    }
    return (del_link2(l, r));
}

void modify_data(t_path *p)
{
    while (p->next)
    {
        p->room->connects = del_link(p->room->connects, p->next->room);
        p = p->next;
    }
}

t_way *get_max(t_way *l)
{
    t_way *ret;

    ret = l;
    while (l)
    {
        if (ret->ants + ret->len < l->ants + l->len && l->ants)
            ret = l;
        l = l->next;
    }
    return (ret);
}

t_way *get_min(t_way *l)
{
    t_way *ret;

    ret = l;
    while (l)
    {
        if (ret->ants + ret->len > l->ants + l->len)
            ret = l;
        l = l->next;
    }
    return (ret);
}

int count_steps(t_way *l, int ants)
{
    t_way  *ret;

    while (ants--)
        (get_min(l)->ants)++;
    ret = get_max(l);
    return (ret->ants + ret->len - 2);
}

t_path  *p_copy(t_path *p)
{
    t_path *tmp;
    t_path *new;

    new = NULL;
    while (p->next)
        p = p->next;
    while (p)
    {
        if (!(tmp = (t_path *)ft_memalloc(sizeof(t_path))))
            exit(1);
        tmp->room = p->room;
        tmp->next = new;
        if (new)
            new->prev = tmp;
        new = tmp;
        p = p->prev;
    }
    return (new);
}

t_way *lst_copy(t_way *l)
{
    t_way  *new;
    t_way *tmp;

    new = NULL;
    while (l->next)
        l = l->next;
    while (l)
    {
        if (!(tmp = (t_way *)ft_memalloc(sizeof(t_way))))
            exit(1);
        tmp->len = l->len;
        tmp->path = p_copy(l->path);
        tmp->ants = l->ants;
        tmp->next = new;
        if (new)
            new->prev = tmp;
        new = tmp;
        l = l->prev;
    }
    return (new);
}

t_way *check_steps(t_way *p_list, t_way *final, int ants)
{
    static int last_count_steps;
    int tmp;

    if (!last_count_steps)
    {
        last_count_steps = count_steps(p_list, ants);
        free_path_list(final);
        return (lst_copy(p_list));
    }

    tmp = count_steps(p_list, ants);
    if (tmp < last_count_steps)
    {
        last_count_steps = tmp;
        free_path_list(final); //неправильно фришит
        return (lst_copy(p_list));
    }
    return (final);
}

void restore_p_list(t_way *l)
{
    while (l)
    {
        l->ants = 0;
        l = l->next;
    }
}

void restore(t_data *data, t_way *p_list)
{
    t_room *rooms;

    rooms = data->rooms;
    while (rooms)
    {
        rooms->room_par = NULL;
        rooms->weight = INF;
        rooms = rooms->next;
    }
    data->start->weight = 0;
    restore_p_list(p_list);
}

void swap(t_way *l1, t_way *l2)
{
    t_way  tmp;

    tmp.len = l1->len;
    tmp.path = l1->path;
    tmp.ants = l1->ants;
    l1->len = l2->len;
    l1->path = l2->path;
    l1->ants = l2->ants;
    l2->len = tmp.len;
    l2->path = tmp.path;
    l2->ants = tmp.ants;
}

void bubble_sort(t_way *l)
{
    int sort;
    t_way *first;

    first = l;
    if (!l)
        return;
    while (1)
    {
        sort = 1;
        while (l->next)
        {
            if (l->len > l->next->len)
            {
                swap(l, l->next);
                sort = 0;
            }
            l = l->next;
        }
        if (sort)
            break;
        l = first;
    }
}

void add_link2(t_connect **l, t_room *dst, int weight)
{
    t_connect *new;
    if (!(new = (t_connect *)ft_memalloc(sizeof(t_connect))))
        exit(1);
    new->next = *l;
    *l = new;
    new->room = dst;
    new->weight = weight;
}

void split_vertex(t_path *vert)
{
    t_room *out;

    if (!(out = (t_room *)ft_memalloc(sizeof(t_room))))
        exit(1);
    out->weight = INF;
    out->connects = vert->room->connects;
    vert->room->connects = NULL;
    add_link2(&out->connects, vert->room, 0);
    add_link2(&vert->room->connects, vert->prev->room->out_part == NULL ?
            vert->prev->room : vert->prev->room->out_part, -1);
    vert->room->out_part = out;
    out->in_part = vert->room;
}

void split(t_way *way)
{
    t_path *p;

    if (!way)
        return;
    while (way)
    {
        p = way->path->next;
        while (p->next)
        {
            split_vertex(p);
            p = p->next;
        }
        way = way->next;
    }
}

void suurb(t_data *data)
{
    int max_path;
    t_path *p;
    t_way *way;

    max_path = get_max_path(data->start, data->end);
    way = NULL;
    while (max_path--)
    {
        split(way);
        if (!(p = bfs(data)))
            break;
        way = plist_push_back(way, p);//
        merge(way);
        if (collision_handle(way, p->next, 0))
            recount_len(way);
        modify_data(p);
        data->ways = check_steps(way, data->ways, data->ants);
        restore(data, way);
    }
    merge(way);
    free_path_list(way);
    bubble_sort(data->ways);
}

int			main(int ac, char **av)
{
	t_data	data;
	char	**str_split;
	char	*map_data;
	int		fd;

	fd = 0;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	data = ft_zerodata();
	map_data = reading_card(&str_split, fd);
	ft_correct(&data, &data.check, str_split);
    set_distance(data.rooms);
	data.start->weight = 0;  // добавила ---- уводит по строкам в ++++
	suurb(&data);
	print_n_free_map_data(&map_data);
	//продебажить
	ft_buff_lem(&data);
	//дебажить
	ft_struct_free(&data);
	return (0);
}


