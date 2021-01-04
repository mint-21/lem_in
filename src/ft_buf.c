#include "lemin.h"

void	add_to_buff(t_way *l, int i)
{
    t_ants	*new;

    if (!(new = (t_ants *)ft_memalloc(sizeof(t_ants))))
        exit(1);
    new->num = i;
    new->curr = l->path;
    if (!(l->last_ant))
        l->buf = new;
    else
        l->last_ant->next = new;
    l->last_ant = new;
}

int		is_empty(t_way *l)
{
    while (l)
    {
        if (l->ants)
            return (1);
        l = l->next;
    }
    return (0);
}

void	fill_buf(t_way *l)
{
    t_way	*first;
    int				i;

    i = 1;
    first = l;
    while (1)
    {
        if (l->ants)
        {
            (l->ants)--;
            add_to_buff(l, i);
            i++;
        }
        if (!is_empty(first))
            break ;
        else if (!(l = l->next))
            l = first;
    }
}