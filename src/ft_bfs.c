#include "lemin.h"

t_room *q_get(t_rooms **q)
{
    t_room	*ret;
    t_rooms *tmp;

    if (!*q)
        return (NULL);
    ret = (*q)->r;
    tmp = *q;
    *q = (*q)->next;
    free(tmp);
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
    while (q)
    {
        free(q);
        q = q->next;
    }
    return (assemble_path(w, data->start));
}