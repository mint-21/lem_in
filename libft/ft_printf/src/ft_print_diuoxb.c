/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di_printuoxb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:47:25 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:47:27 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	ft_get_sign(t_options *f, unsigned long long *unum, long long num)
{
	char	sign;

	*unum = num;
	sign = 0;
	if (num < 0)
	{
		sign = '-';
		*unum = -num;
		f->width--;
	}
	else if (f->flags & F_PLUS)
	{
		sign = '+';
		f->width--;
	}
	else if (f->flags & F_SP)
	{
		sign = ' ';
		f->width--;
	}
	if (f->flags & F_MINUS || f->sum >= 0)
		f->flags &= ~F_NULL;
	return (sign);
}

void	ft_help_di_print(t_options *f, t_buff *buf, char sign)
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

void	ft_di_print(t_options *f, t_buff *buf, long long num)
{
	unsigned long long	unum;
	char				sign;
	char				number[MAX_DEC];
	char				*temp;
	int					len;

	sign = ft_get_sign(f, &unum, num);
	len = 0;
	if (!unum)
		number[len++] = '0';
	else
		len = ft_itoa_base(unum, number, 10, f->flags & F_LOWER);
	if (len > f->sum && (f->sum || num))
		f->sum = len;
	else
		f->sum = f->sum;
	f->width -= f->sum;
	ft_help_di_print(f, buf, sign);
	ft_p_printrec(buf, f->sum, len);
	temp = number;
	while (len-- && (f->sum || num))
		ft_push(buf, *temp++);
	ft_print_width(buf, &f->width, ' ');
}

void	ft_reset_options(t_options *f, int num)
{
	if (f->flags & F_MINUS)
		f->flags &= ~F_NULL;
	if (f->flags & F_SHARP)
	{
		if (f->base == 16 && !num)
			f->width -= 2;
		else if (f->base == 8 && !num)
		{
			f->width -= 1;
			f->sum -= 1;
		}
		else if (f->base == 2)
			f->width -= 2;
	}
	if (f->width < 0 && f->sum == 0)
		f->width = 0;
}
