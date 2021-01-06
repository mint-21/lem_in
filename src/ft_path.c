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

t_way *max_path(t_data *data, t_way *way)
{
    int max_path;
    t_path *p;

    while ((max_path = get_max_path(data->start, data->end)) > 0)
    {
        --max_path;
        split(way);
        if (!(p = bfs(data)))
            break;
        way = plist_push_back(way, p);
        merge(way);
        if (collision_handle(way, p->next, 0))
            recount_len(way);
        modify_data(p);
        data->ways = check_steps(way, data->ways, data->ants);
        restore(data, way);
    }
    return (way);
}
