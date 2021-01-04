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