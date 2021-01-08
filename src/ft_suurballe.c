#include "lemin.h"

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

void recount_len(t_way *l)
{
    while (l)
    {
        l->len = p_len(l->path);
        l = l->next;
    }
}

t_way *plist_push_back(t_way *way, t_path *p, int len)
{
    t_way *first;
    t_way *new;
    t_path *w;

    w = p;
    first = way;
    if (!(new = (t_way *)ft_memalloc(sizeof(t_way))))
        exit(1);
    while (w)
    {
        w = w->next;
        len++;
    }
    new->len = len;
    new->path = p;
    if (!first)
        return (new);
    while (way->next)
        way = way->next;
    way->next = new;
    new->prev = way;
    return (first);
}

void suurb(t_data *data)
{
    t_way *way;
    t_room *rooms;
    int len;

    len = 0;
    rooms = data->rooms;
    while (rooms)
    {
        rooms->weight = INF;
        rooms = rooms->next;
    }
    data->start->weight = 0;
    way = NULL;
    way = max_path(data, way, len);
    merge(way);
    free_list(way);
    bubble_sort(data->ways);
}