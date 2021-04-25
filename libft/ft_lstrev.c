/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:37:51 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 14:41:46 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **beginlst)
{
	t_list	*list;
	t_list	*a;
	t_list	*b;

	list = *beginlst;
	if (!list)
		return ;
	if (!list->next)
		return ;
	a = list->next;
	b = a->next;
	list->next = NULL;
	a->next = list;
	while (b)
	{
		list = a;
		a = b;
		b = a->next;
		a->next = list;
	}
	*beginlst = a;
}
