/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:58 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:47:59 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_print_width(t_buff *buf, int *width, char c)
{
	while ((*width)-- > 0)
		ft_push(buf, c);
}

void	ft_p_printrec(t_buff *buf, int sum, int len)
{
	while (len < sum--)
		ft_push(buf, '0');
}

void	ft_s_printharp(t_buff *buf, t_options *f)
{
	if (f->base == 16)
	{
		ft_push(buf, '0');
		ft_push(buf, 'X' | (f->flags & F_LOWER));
	}
	if (f->base == 8)
		ft_push(buf, '0');
	else if (f->base == 2)
	{
		ft_push(buf, '0');
		ft_push(buf, 'b');
	}
}
