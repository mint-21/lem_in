#include "lemin.h"

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