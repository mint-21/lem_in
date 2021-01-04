#include "lemin.h"

t_connect *del_link2(t_connect *l, t_room *r)
{
    t_connect *prev;
    t_connect *first;

    prev = NULL;
    first = l;
    while (l)
    {
        if (l->room == r)
        {
            if (prev)
                prev->next = l->next;
            else
                first = first->next;
            free(l);
            break;
        }
        prev = l;
        l = l->next;
    }
    return (first);
}

t_connect *del_link(t_connect *l, t_room *r)
{
    if (!l)
        return (NULL);
    if (!l->next)
    {
        free(l);
        return (NULL);
    }
    return (del_link2(l, r));
}

t_connect *del_zero_link(t_connect *l)
{
    t_connect *f;
    t_connect *prev;

    f = l;
    prev = NULL;
    while (l)
    {
        if (l->weight == 0)
        {
            if (!prev)
                f = l->next;
            else
                prev->next = l->next;
            free(l);
            break;
        }
        l = l->next;
        prev = l;
    }
    return (f);
}

t_ants	*buf_delete_ant(t_ants **buf, t_ants *ant)
{
    t_ants *tmp;
    t_ants *ret;

    if (*buf == ant)
        *buf = (*buf)->next;
    else
    {
        tmp = *buf;
        while (tmp->next != ant)
            tmp = tmp->next;
        tmp->next = ant->next;
    }
    ret = ant->next;
    free(ant);
    return (ret);
}
