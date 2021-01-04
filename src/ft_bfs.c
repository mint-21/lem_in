#include "lemin.h"

void q_free(t_rooms *q)
{
    if (!q)
        return;
    q_free(q->next);
    free(q);
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