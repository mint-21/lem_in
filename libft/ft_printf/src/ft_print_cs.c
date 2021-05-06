/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:16 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:47:17 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_c_print(t_options *f, t_buff *buf, unsigned char c)
{
	f->width--;
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
	ft_push(buf, c);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

wchar_t	ft_convert_to_utf8_help(wchar_t c, char *lc, int bytes)
{
	if (++bytes && c <= 0x7F)
		lc[0] = c;
	else if (++bytes && c <= 0x7FF)
	{
		lc[0] = 0xC0 | (c >> 6);
		lc[1] = 0x80 | (c & 0x3F);
	}
	else if (++bytes && c <= 0xFFFF)
	{
		lc[0] = 0xE0 | (c >> 12);
		lc[1] = 0x80 | ((c >> 6) & 0x3F);
		lc[2] = 0x80 | (c & 0x3F);
	}
	else if (++bytes && c <= 0x10FFFF)
	{
		lc[0] = 0xF0 | (c >> 18);
		lc[1] = 0x80 | ((c >> 12) & 0x3F);
		lc[2] = 0x80 | ((c >> 6) & 0x3F);
		lc[3] = 0x80 | (c & 0x3F);
	}
	return (c);
}

int	ft_convert_to_utf8(wchar_t c, char *lc)
{
	int		bytes;

	bytes = 0;
	c = ft_convert_to_utf8_help(c, lc, bytes);
	if (c <= 0x10FFFF)
		return (bytes);
	else
		return (0);
}

void	ft_lc_print(t_options *f, t_buff *buf, wchar_t c)
{
	int		bytes;
	char	lc[4];
	char	*temp;

	bytes = ft_convert_to_utf8(c, lc);
	f->width -= bytes;
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
	temp = lc;
	while (bytes--)
		ft_push(buf, *temp++);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

void	ft_s_print(t_options *f, t_buff *buf, char *str)
{
	int		len;

	if (!str)
		str = "(null)";
	len = ft_strnlen(str, f->sum);
	f->width -= len;
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
	while (len--)
		ft_push(buf, *str++);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}
