/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:58:22 by asmall            #+#    #+#             */
/*   Updated: 2020/07/27 20:57:48 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Заменяем ребра из найденного кратчайшего пути обратными ребрами с отриц весом
*/

#include "lemin.h"

void		redirection_conditions(t_connect *connect, t_room *src)
{
	if (connect->prev)
		connect->prev->next = connect->next;
	else
		src->connects = connect->next;
	if (connect->next)
		connect->next->prev = connect->prev;
	if (connect->weight == -1)
		connect->weight = 2;
	else
		connect->weight = -1;
}

void	ft_redirection_connect(t_room *src, t_room *dst, t_connect *connect)
{
	connect->room = src;
	connect->room_one = dst;
	connect->prev = NULL;
	connect->next = dst->connects;
	if (dst->connects)
		dst->connects->prev = connect;
	dst->connects = connect;
}