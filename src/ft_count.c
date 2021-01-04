#include "lemin.h"

int count_link(t_room *room)
{
    int ret;
    t_connect *tmp;

    ret = 0;
    tmp = room->connects;
    while (tmp)
    {
        tmp = tmp->next;
        ret++;
    }
    return (ret);
}

int get_max_path(t_room *start, t_room *end)
{
    int s_link;
    int e_link;

    s_link = count_link(start);
    e_link = count_link(end);
    if (s_link > e_link)
        return (e_link);
    return (s_link);
}
