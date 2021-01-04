#include "lemin.h"

void restore_p_list(t_way *l)
{
    while (l)
    {
        l->ants = 0;
        l = l->next;
    }
}

void restore(t_data *data, t_way *p_list)
{
    t_room *rooms;

    rooms = data->rooms;
    while (rooms)
    {
        rooms->room_par = NULL;
        rooms->weight = INF;
        rooms = rooms->next;
    }
    data->start->weight = 0;
    restore_p_list(p_list);
}

void swap(t_way *l1, t_way *l2)
{
    t_way  tmp;

    tmp.len = l1->len;
    tmp.path = l1->path;
    tmp.ants = l1->ants;
    l1->len = l2->len;
    l1->path = l2->path;
    l1->ants = l2->ants;
    l2->len = tmp.len;
    l2->path = tmp.path;
    l2->ants = tmp.ants;
}

void bubble_sort(t_way *l)
{
    int sort;
    t_way *first;

    first = l;
    if (!l)
        return;
    while (1)
    {
        sort = 1;
        while (l->next)
        {
            if (l->len > l->next->len)
            {
                swap(l, l->next);
                sort = 0;
            }
            l = l->next;
        }
        if (sort)
            break;
        l = first;
    }
}