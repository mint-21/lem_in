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

void bubble_sort(t_way *l, t_way *first)
{
    int sort;
    t_way  tmp;

    while (1)
    {
        sort = 1;
        while (l->next)
        {
            if (l->len > l->next->len)
            {
                ft_swap(&(l)->len, &(l->next)->len);
                ft_swap(&(l)->ants, &(l->next)->ants);
                tmp.path = l->path;
                l->path = l->next->path;
                l->next->path = tmp.path;
                sort = 0;
            }
            l = l->next;
        }
        if (sort)
            break;
        l = first;
    }
}
