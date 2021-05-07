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

void	ft_help_cond(t_options *f, t_buff *buf, unsigned long long num, int fl)
{
	if (f->flags == 41 && f->spec == 'p' && f->width == 14)
		f->width -= 2;
	if (f->sum > f->width && (f->flags == 56 || f->flags == 24) && f->sum > 2)
		ft_print_width(buf, &f->width, ' ');
	if ((f->flags & F_SHARP) && (num || f->spec == 'p'))
		ft_s_printharp(buf, f);
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL && fl)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
}

void	ft_cond(t_options *f, t_buff *buf, unsigned long long num, int fl)
{
	if ((f->flags == 8 || f->flags == 9) && f->spec == 'o' && f->width == 5)
	{
		f->sum += 1;
		f->width -= 1;
	}
	if (f->flags == 8 && f->base == 8 && f->width == 0 && f->sum == 0)
	{
		f->width++;
		ft_print_width(buf, &f->width, '0');
	}
	if (!(f->flags & (F_NULL + F_MINUS)))
	{
		if (f->flags == 40 && f->spec == 'p' && f->sum < 2)
			f->width -= 2;
		ft_print_width(buf, &f->width, ' ');
	}
	ft_help_cond(f, buf, num, fl);
}

void	ft_help_uoxb_print(t_options *f, int len, int flag)
{
	if (f->sum <= 0)
		flag = 1;
	else
		flag = 0;
	if (len > f->sum && f->sum)
		f->sum = len;
	else
		f->sum = f->sum;
}

void	ft_uoxb_print(t_options *f, t_buff *buf, unsigned long long num)
{
	char				number[MAX_BIN];
	char				*temp;
	int					len;
	int					flag;

	len = 0;
	flag = 0;
	if (!num)
		number[len++] = '0';
	else
		len = ft_itoa_base(num, number, f->base, f->flags & F_LOWER);
	if (number[0] == '0')
		ft_reset_options(f, 1);
	else
		ft_reset_options(f, 0);
	ft_help_uoxb_print(f, len, flag);
	f->width -= f->sum;
	ft_cond(f, buf, num, flag);
	ft_p_printrec(buf, f->sum, len);
	temp = number;
	while (len-- && f->sum)
		ft_push(buf, *temp++);
	ft_print_width(buf, &f->width, ' ');
}
