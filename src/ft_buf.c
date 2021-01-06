/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:10:47 by asmall            #+#    #+#             */
/*   Updated: 2021/01/06 15:25:29 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_in_buff(t_way *way, int i)
{
    t_ants	*new;

    if (!(new = (t_ants *)ft_memalloc(sizeof(t_ants))))
        exit(1);
    way->ants -= 1;
    new->num = i;
    new->curr = way->path;
    (!(way->last_ant)) ? (way->buf = new) : (way->last_ant->next = new);
    way->last_ant = new;
}

void	fill_buf(t_way *way)
{
    t_way	*head;
    int		count;

    count = 1;
    head = way;
    while (1)
    {
        if (way->ants)
            add_in_buff(way, count++);
        if (!check_empty(head))
            break ;
        else if (!(way = way->next))
            way = head;
    }
}
