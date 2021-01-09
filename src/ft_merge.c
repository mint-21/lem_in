#include "lemin.h"

void in_part(t_path *vert)
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

void out_part(t_path *p)
{
    free_links(p->room->connects);
    p->room->out_part->connects = del_zero_link(p->room->out_part->connects);
    p->room->connects = p->room->out_part->connects;
}

void merge(t_way *way, t_rooms *buf)
{
    t_path *p;

    while (way)
    {
        p = way->path->next;
        while (p->next)
        {
            if (p->room->out_part) {
                out_part(p);
                buf = add_to_buf(p->room->out_part, buf);
            }
            else if (p->room->in_part)
                in_part(p);
            p->room->in_part = NULL;
            p->room->out_part = NULL;
            p = p->next;
        }
        way = way->next;
    }
    free_buf(buf);
}
