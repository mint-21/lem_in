/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:48:39 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 14:38:10 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newl;

	if (!lst || !f)
		return (NULL);
	newl = malloc(sizeof(t_list));
	if (!(newl))
		return (NULL);
	*newl = *f(lst);
	if (lst->next)
	{
		newl->next = ft_lstmap(lst->next, f);
		if (!newl->next)
		{
			free(newl->content);
			free(newl);
			return (NULL);
		}
	}
	return (newl);
}
