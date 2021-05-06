/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_nums.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:05 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:47:07 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_parse_num(t_options *f, t_buff *buf, long long num)
{
	if (f->spec == 'D')
		ft_di_print(f, buf, (long)num);
	else if (f->length == 0)
		ft_di_print(f, buf, (int)num);
	else if (f->length == LEN_HH)
		ft_di_print(f, buf, (char)num);
	else if (f->length == LEN_H)
		ft_di_print(f, buf, (short)num);
	else if (f->length == LEN_L)
		ft_di_print(f, buf, (long)num);
	else if (f->length == LEN_LL)
		ft_di_print(f, buf, (long long)num);
	else if (f->length == LEN_J)
		ft_di_print(f, buf, (intmax_t)num);
	else if (f->length == LEN_Z)
		ft_di_print(f, buf, (ssize_t)num);
}

void	ft_parse_unum(t_options *f, t_buff *buf, unsigned long long unum)
{
	if (f->spec == 'U' || f->spec == 'O')
		ft_uoxb_print(f, buf, (unsigned long)unum);
	else if (f->length == 0)
		ft_uoxb_print(f, buf, (unsigned int)unum);
	else if (f->length == LEN_HH)
		ft_uoxb_print(f, buf, (unsigned char)unum);
	else if (f->length == LEN_H)
		ft_uoxb_print(f, buf, (unsigned short)unum);
	else if (f->length == LEN_L)
		ft_uoxb_print(f, buf, (unsigned long)unum);
	else if (f->length == LEN_LL)
		ft_uoxb_print(f, buf, (unsigned long long)unum);
	else if (f->length == LEN_J)
		ft_uoxb_print(f, buf, (uintmax_t)unum);
	else if (f->length == LEN_Z)
		ft_uoxb_print(f, buf, (size_t)unum);
}

char	ft_parse_help(t_fnum fnum)
{
	if (fnum.num.ll & (1ULL << 63))
		fnum.sign = 1;
	else
		fnum.sign = 0;
	return (fnum.sign);
}

void	ft_parse_fnum(t_options *f, t_buff *buf, double num, \
				void (*ft_print)(t_options*, t_buff*, t_fnum*))
{
	t_fnum	fnum;

	fnum.num.f = num;
	fnum.sign = ft_parse_help(fnum);
	fnum.exp = ((fnum.num.ll >> 52) & 0x7FF) - 1023;
	fnum.man = (fnum.num.ll & 0x1FFFFFFFFFFFFF) | 0x10000000000000;
	fnum.ipoint = NULL;
	fnum.fpoint = NULL;
	fnum.zero = 0;
	if (fnum.exp >= 52)
		fnum.ipoint = ft_get_part(fnum.man, fnum.exp - 52, ft_get_ip);
	else if (fnum.exp >= 0)
	{
		fnum.ipoint = ft_get_part(fnum.man >> (52 - fnum.exp), 0, ft_get_ip);
		fnum.fpoint = ft_get_part(fnum.man << (fnum.exp + 12), 0, ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man << (fnum.exp + 12), 0, fnum.fpoint);
	}
	else if (fnum.exp >= -1022)
	{
		fnum.fpoint = ft_get_part(fnum.man << 11, -(fnum.exp + 1), ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man << 11, -(fnum.exp + 1), fnum.fpoint);
	}
	ft_print(f, buf, &fnum);
	ft_strdel(&fnum.ipoint);
	ft_strdel(&fnum.fpoint);
}
