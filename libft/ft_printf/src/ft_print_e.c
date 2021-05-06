/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_e_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:36 by asmall            #+#    #+#             */
/*   Updated: 2020/01/26 14:47:38 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_set_exp(char *number, t_fnum *fnum, char spec)
{
	int		numlen;

	*number++ = spec;
	if (fnum->fpoint && !fnum->ipoint)
		*number++ = '-';
	else
		*number++ = '+';
	if (fnum->fpoint && !fnum->ipoint)
	{
		numlen = ft_unumlen(fnum->zero, 10);
		if (numlen < 2)
			*number++ = '0';
		number += ft_itoa_base(fnum->zero + 1, number, 10, 0);
	}
	else
	{
		numlen = ft_strnlen(fnum->ipoint, -1);
		if (!fnum->ipoint || (numlen < 11))
			*number++ = '0';
		if (!fnum->ipoint || numlen == 1)
			*number++ = '0';
		else
			number += ft_itoa_base(numlen - 1, number, 10, 0);
	}
	*number = '\0';
}

int	ft_get_first_enum(char *number, char **ipoint, char **fpoint)
{
	int		i;

	i = 0;
	if (!*ipoint && !*fpoint)
		number[i++] = '0';
	else
	{
		if (*ipoint)
			number[i++] = *(*ipoint)++;
		else
			number[i++] = *(*fpoint)++;
	}
	number[i++] = '.';
	return (i);
}

char	*ft_get_enum(t_fnum *fnum, int sum, int ilen, char spec)
{
	int		i;
	int		zero;
	char	*ipoint;
	char	*fpoint;
	char	*number;

	number = (char *)malloc(ilen + sum + 2);
	ipoint = fnum->ipoint;
	fpoint = fnum->fpoint;
	zero = fnum->zero;
	i = ft_get_first_enum(number, &ipoint, &fpoint);
	while (ipoint && *ipoint && (i < sum + 1))
		number[i++] = *ipoint++;
	while (ipoint && zero-- && (i < sum + 1))
		number[i++] = '0';
	while (fpoint && *fpoint && (i < sum + 1))
		number[i++] = *fpoint++;
	while (i < sum + 1)
		number[i++] = '0';
	ft_round(number, --i);
	if (sum == 2)
		--i;
	ft_set_exp(&number[i], fnum, spec);
	return (number);
}

void	ft_help_print_e(t_options *f, t_buff *buf, char sign)
{
	if (!(f->flags & (F_NULL + F_MINUS)))
		ft_print_width(buf, &f->width, ' ');
	if (sign)
		ft_push(buf, sign);
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
}

void	ft_e_print(t_options *f, t_buff *buf, t_fnum *fnum)
{
	char	sign;
	char	*number;
	char	*temp;
	int		len;
	int		numlen;

	sign = ft_get_sign_f(f, fnum->sign);
	numlen = ft_unumlen(fnum->zero + 1, 10);
	if (numlen < 2)
		len = 5;
	else
		len = numlen + 3;
	if (f->sum)
		f->width -= f->sum + len + 1;
	else
		f->width -= len;
	ft_help_print_e(f, buf, sign);
	number = ft_get_enum(fnum, f->sum + 2, len, f->spec);
	temp = number;
	while (*temp)
		ft_push(buf, *temp++);
	ft_strdel(&number);
	ft_print_width(buf, &f->width, ' ');
}
