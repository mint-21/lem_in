/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:50:26 by asmall            #+#    #+#             */
/*   Updated: 2021/04/21 14:53:33 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_way	*get_max(t_way *l)
{
	t_way	*ret;

	ret = l;
	while (l)
	{
		if (ret->ants + ret->len < l->ants + l->len && l->ants)
			ret = l;
		l = l->next;
	}
	return (ret);
}

t_way	*get_min(t_way *l)
{
	t_way	*ret;

	ret = l;
	while (l)
	{
		if (ret->ants + ret->len > l->ants + l->len)
			ret = l;
		l = l->next;
	}
	return (ret);
}

int	count_steps(t_way *l, int ants)
{
	t_way	*ret;

	while (ants--)
		(get_min(l)->ants)++;
	ret = get_max(l);
	return (ret->ants + ret->len - 2);
}

t_way	*check_steps(t_way *p_list, t_way *final, int ants)
{
	static int	last_count_steps;
	int			tmp;

	if (!last_count_steps)
	{
		last_count_steps = count_steps(p_list, ants);
		free_list(final);
		return (lst_copy(p_list));
	}
	tmp = count_steps(p_list, ants);
	if (tmp < last_count_steps)
	{
		last_count_steps = tmp;
		free_list(final);
		return (lst_copy(p_list));
	}
	return (final);
}
