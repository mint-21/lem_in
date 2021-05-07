/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correct_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:39 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 14:45:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	ft_return_path(int i, int j)
{
	if (j < i)
		return (j);
	else
		return (i);
}

int	get_max_path(t_room *start, t_room *end)
{
	int			i;
	int			j;
	t_connect	*ptr;
	t_connect	*src;

	ptr = start->connects;
	src = end->connects;
	i = 0;
	j = 0;
	while (ptr || src)
	{
		if (ptr)
		{
			ptr = ptr->next;
			i++;
		}
		else if (src)
		{
			src = src->next;
			j++;
		}
	}
	return (ft_return_path(i, j));
}
