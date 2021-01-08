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

t_path *bfs(t_data *data, int len)
{
    t_room *w;
    t_rooms *q;
    t_path *p;

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
    p = NULL;
    while (w != data->start)
    {
        p = p_push_begin(w, p);
        w = w->room_par;
        len++;
    }
    p = p_push_begin(data->start, p);
    return (p);
}