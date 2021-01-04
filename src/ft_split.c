#include "lemin.h"

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