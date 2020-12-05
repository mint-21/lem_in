/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff_lem_buff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:21:00 by asmall            #+#    #+#             */
/*   Updated: 2020/07/05 19:21:04 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** We store it in the buffer for output to the console (L1-name).
** Add an ant to the room, and from which we left - remove the ant
*/

void		copy_text_buff(t_data *data, t_path *path, t_buf *buf, int ant)
{
	int		j;

	j = -1;
	(buf->space) ? ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE, ' ')
		: (buf->space = 1);
	ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE, 'L');
	ft_putnbr_buf(buf->str, &buf->i, BUFF_SIZE, ant);
	ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE, '-');
	while (path->prev->room->name[++j])
		ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE,
				path->prev->room->name[j]);
	if (path->prev->room != data->end)
		path->prev->room->ant = ant;
	else
		path->prev->room->ant = path->prev->room->ant + 1;
	if (path->room == data->start)
		--path->room->ant;
	else
		path->room->ant = 0;
}

/*
** The function prints each step to the console
** ft_step: buffered the text one step per path
*/

void	teleport_all(char *name, int ants)
{
    int i;

    i = 1;
    while (i <= ants)
    {
        ft_printf("L%d-%s ", i, name);
        i++;
    }
    ft_printf("\n");
}

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

int		print_step(t_ants **buf, int step)
{
    t_ants *tmp;

    if (!*buf)
        return (0);
    tmp = *buf;
    while (tmp && step--)
    {
        tmp->curr = tmp->curr->next;
        ft_printf("L%d-%s ", tmp->num, tmp->curr->room->name);
        if (!tmp->curr->prev->prev)
            return (1);
        if (!tmp->curr->next)
            tmp = buf_delete_ant(buf, tmp);
        else
            tmp = tmp->next;
    }
    return (1);
}

int		print_line(t_way *l, int step)
{
    int ret;

    ret = 0;
    while (l)
    {
        ret += print_step(&l->buf, step);
        l = l->next;
    }
    return (ret);
}

void		ft_buff_lem(t_data *data)
{
	int		steps;

	steps = 0;
	if (data->ways->len == 2)
    {
	    teleport_all(data->ways->path->next->room->name, data->ants);
        free_path_list(data->ways);
        return ;
    }
    fill_buf(data->ways);
    while (print_line(data->ways, ++steps))
        ft_printf("\n");
    free_path_list(data->ways);
}
