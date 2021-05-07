/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaning_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:41:51 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/17 14:34:56 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	restore_col(t_path *start, t_path *end)
{
	if (start == end)
		return ;
	restore_col(start->next, end);
	free(start);
}

t_path	*remove_collision(t_path *col_start1, t_path *col_end2)
{
	t_path	*col_start2;
	t_path	*col_end1;

	col_start2 = col_end2;
	col_end1 = col_start1;
	while (col_start2->prev->room == col_end1->next->room)
	{
		col_start2 = col_start2->prev;
		col_end1 = col_end1->next;
	}
	restore_col(col_start1->next, col_end1);
	restore_col(col_start2->next, col_end2);
	col_start1->next = col_end2->next;
	col_start1->next->prev = col_start1;
	col_start2->next = col_end1->next;
	col_start2->next->prev = col_start2;
	free(col_end1);
	free(col_end2);
	return (col_start2);
}

t_path	*find_room(t_way *l, t_room *tofind, t_path *ap)
{
	t_path	*tmp;

	while (l)
	{
		if (l->path != ap)
		{
			tmp = l->path;
			while (tmp)
			{
				if (tmp->room == tofind)
					return (tmp);
				tmp = tmp->next;
			}
		}
		l = l->next;
	}
	return (NULL);
}

int	collision_handle(t_way *list, t_path *p, int ret)
{
	t_path	*tmp;
	t_path	*first;
	t_path	*w;

	w = p;
	while (w->prev)
		w = w->prev;
	first = w;
	while (p->next)
	{
		tmp = find_room(list, p->room, first);
		if (tmp)
		{
			ret = 1;
			p = remove_collision(p, tmp);
			w = p;
			while (w->prev)
				w = w->prev;
			first = w;
		}
		else
			p = p->next;
	}
	return (ret);
}
