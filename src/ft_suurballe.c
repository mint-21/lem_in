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
    free_list(way);
    bubble_sort(data->ways);
}