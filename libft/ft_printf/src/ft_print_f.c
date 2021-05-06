/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_f_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:47 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:47:49 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_round(char *number, int len)
{
	int		count;

	count = len;
	if (number[len] >= '5')
	{
		number[len--] = '\0';
		while (len >= 0)
		{
			if (number[len] == '9')
				number[len] = '0';
			else if (number[len] != '.')
				break ;
			len--;
		}
		if (len >= 0)
			number[len] += 1;
		else
		{
			ft_memmove(number + 1, number, count);
			number[0] = '1';
		}
	}
	else
		number[len] = '\0';
}

char	ft_get_sign_f(t_options *f, char sign)
{
	char	res;

	res = 0;
	if (sign)
	{
		res = '-';
		f->width--;
	}
	else if (f->flags & F_PLUS)
	{
		res = '+';
		f->width--;
	}
	else if (f->flags & F_SP)
	{
		res = ' ';
		f->width--;
	}
	if (f->flags & F_MINUS)
		f->flags &= ~F_NULL;
	if (f->sum == -1)
		f->sum = 6;
	return (res);
}

void	ft_help_print_f(t_options *f, int len, t_buff *buf, char sign)
{
	if (f->flags == 9 || f->flags == 11 || f->flags == 13)
	{
		if (f->sum)
			f->width -= f->sum + len + 1;
		else
			f->width -= len + 1;
	}
	else
	{
		if (f->sum)
			f->width -= f->sum + len + 1;
		else
			f->width -= len;
	}
	if (!(f->flags & (F_NULL + F_MINUS)))
		ft_print_width(buf, &f->width, ' ');
	if (sign)
		ft_push(buf, sign);
}

void	ft_f_print(t_options *f, t_buff *buf, t_fnum *fnum)
{
	int		len;
	char	sign;
	char	*number;
	char	*temp;

	sign = ft_get_sign_f(f, fnum->sign);
	len = 0;
	if (!fnum->ipoint)
		len++;
	else
		len = ft_strnlen(fnum->ipoint, -1);
	ft_help_print_f(f, len, buf, sign);
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
	number = ft_get_fnum(fnum, f->sum, len, f);
	temp = number;
	while (*temp)
		ft_push(buf, *temp++);
	ft_strdel(&number);
	ft_print_width(buf, &f->width, ' ');
}
