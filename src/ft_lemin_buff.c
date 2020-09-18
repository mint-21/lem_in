/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:21:00 by asmall            #+#    #+#             */
/*   Updated: 2020/07/05 19:21:04 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** В буфер запоминаем для вывода на консоль (L1-name).
** В комнату добавляем муравья, а из которой вышли - убираем муравья
*/

void	copy_text_buff(t_data *data, t_path *path, t_buf *buf, int ant)
{
	int j;

	j = -1;
	if (data->flags.ways == 0)
	{
		(buf->space) ? ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE, ' ')
		: (buf->space = 1);
		ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE, 'L');
		ft_putnbr_buf(buf->str, &buf->i, BUFF_SIZE, ant);
		ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE, '-');
		while (path->prev->room->name[++j])
			ft_putchar_buf(buf->str, &buf->i, BUFF_SIZE,
					path->prev->room->name[j]);
	}
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
** Функция выводит на консоль каждый шаг.
** ft_step: заносит в буфер текст по одному шагу на каждый путь.
*/

void		ft_lemin(t_data *data)
{
	int		ant;
	t_buf	buf;
	int		steps;

	data->start->ant = data->ants;
	ant = 0;
	buf.i = 0;
	steps = data->best_opt->steps;
	while (steps)
	{
		ft_step(data, &ant, &buf, steps);
		if (data->flags.ways == 0)
			ft_putchar_buf(buf.str, &buf.i, BUFF_SIZE, '\n');
		--steps;
	}
	if (data->flags.ways == 0)
		write(1, buf.str, buf.i);
}
