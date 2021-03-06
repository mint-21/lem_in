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

char	ft_parse_lfnum_help(t_fnum fnum)
{
	if (*(&fnum.num.ll + 1) & (1ULL << 15))
		fnum.sign = 1;
	else
		fnum.sign = 0;
	return (fnum.sign);
}

void	ft_parse_lfnum(t_options *f, t_buff *buf, long double num,
				void (*ft_print)(t_options*, t_buff*, t_fnum*))
{
	t_fnum	fnum;

	fnum.num.lf = num;
	fnum.sign = ft_parse_lfnum_help(fnum);
	fnum.exp = (*(&fnum.num.ll + 1) & 0x7FFF) - 16383;
	fnum.man = fnum.num.ll;
	fnum.ipoint = NULL;
	fnum.fpoint = NULL;
	fnum.zero = 0;
	if (fnum.exp >= 64)
		fnum.ipoint = ft_get_part(fnum.man, fnum.exp - 63, ft_get_ip);
	else if (fnum.exp >= 0)
	{
		fnum.ipoint = ft_get_part(fnum.man >> (63 - fnum.exp), 0, ft_get_ip);
		fnum.fpoint = ft_get_part(fnum.man << (fnum.exp + 1), 0, ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man << (fnum.exp + 1), 0, fnum.fpoint);
	}
	else if (fnum.exp >= -16382)
	{
		fnum.fpoint = ft_get_part(fnum.man, -(fnum.exp + 1), ft_get_fp);
		fnum.zero = ft_get_zero(fnum.man, -(fnum.exp + 1), fnum.fpoint);
	}
	ft_print(f, buf, &fnum);
	ft_strdel(&fnum.ipoint);
	ft_strdel(&fnum.fpoint);
}
