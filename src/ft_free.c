#include "lemin.h"

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

void free_buf(t_rooms *buf)
{
    if (!buf)
        return;
    free_buf(buf->next);
    free(buf->r);
    free(buf);
}

void free_links(t_connect *l)
{
    if (!l)
        return;
    free_links(l->next);
    free(l->next);
    free(l);
}