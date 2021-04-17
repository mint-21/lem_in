/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:02:42 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 14:50:51 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_path(t_path *p)
{
	if (!p)
		return ;
	free_path(p->next);
	free(p);
}

void	free_list(t_way *list)
{
	if (!list)
		return ;
	free_list(list->next);
	free_path(list->path);
	free(list);
}

void	free_buf(t_rooms *buf)
{
	if (!buf)
		return ;
	free_buf(buf->next);
	free(buf->r);
	free(buf);
}

void	free_links(t_connect *l)
{
	if (!l)
		return ;
	free_links(l->next);
	free(l->next);
	free(l);
}
