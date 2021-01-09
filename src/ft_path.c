#include "lemin.h"


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

t_way *add_data(t_path *p, t_data *data, t_way *way)
{
    while (p->next)
    {
        p->room->connects = del_link(p->room->connects, p->next->room);
        p = p->next;
    }
    data->ways = check_steps(way, data->ways, data->ants);
    restore(data, way);
    return (way);
}

t_way *max_path(t_data *data, t_way *way, int len, t_rooms *buf)
{
    int max_path;
    t_path *p;

    while ((max_path = get_max_path(data->start, data->end)) > 0)
    {
        --max_path;
        split(way);
        if (!(p = bfs(data, len)))
            break;
        way = plist_push_back(way, p, len);
        merge(way, buf);
        if (collision_handle(way, p->next, 0))
            recount_len(way);
        way = add_data(p, data, way);
    }
    return (way);
}
