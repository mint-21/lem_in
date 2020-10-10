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

void		ft_buff_lem(t_data *data)
{
	t_buf	buf;
	int		steps;
	t_way	*way;

	data->start->ant = data->ants;
	buf.i = 0;
	steps = data->best_opt->steps;
	way = data->best_opt->ways;
	while (steps)
		steps = ft_step(data, &buf, steps, way);
	write(1, buf.str, buf.i);
}
