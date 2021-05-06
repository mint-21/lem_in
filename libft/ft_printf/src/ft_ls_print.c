/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:48:21 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:48:23 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_ls_print_help(t_options *f, t_buff *buf)
{
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
}

void	ft_ls_print(t_options *f, t_buff *buf, wchar_t *str)
{
	int		len;
	int		bytes;
	char	lc[4];
	char	*temp;

	if (!str)
		str = L"(null)";
	len = ft_wstrnlen(str, f->sum);
	f->width -= len;
	ft_ls_print_help(f, buf);
	bytes = 0;
	while (len)
	{
		bytes = ft_convert_to_utf8(*str++, lc);
		len -= bytes;
		temp = lc;
		while (bytes--)
			ft_push(buf, *temp++);
	}
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}
