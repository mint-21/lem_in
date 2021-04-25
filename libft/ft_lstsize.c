/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:24:42 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 14:41:50 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstsize(t_list *lst)
{
	size_t	s;
	t_list	*tmp;

	s = 0;
	if (lst)
	{
		tmp = lst;
		while (tmp)
		{
			tmp = tmp->next;
			s++;
		}
	}
	return (s);
}
