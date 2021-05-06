/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_printrk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:48:08 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:48:10 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_p_print(t_options *f, t_buff *buf, void *pointer)
{
	unsigned long long	addr;

	addr = (unsigned long long)pointer;
	f->base = 16;
	f->flags |= F_LOWER;
	f->flags |= F_SHARP;
	ft_uoxb_print(f, buf, addr);
}

void	ft_r_printand(t_options *f, t_buff *buf)
{
	f->width--;
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
	ft_push(buf, f->spec);
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

void	ft_r_print(t_options *f, t_buff *buf, char *str)
{
	int	len;

	if (!str)
		str = "(null)";
	len = ft_rstrnlen(str, f->sum);
	f->width -= len;
	if (!(f->flags & F_MINUS))
	{
		if (f->flags & F_NULL)
			ft_print_width(buf, &f->width, '0');
		else
			ft_print_width(buf, &f->width, ' ');
	}
	while (len--)
	{
		if ((*str >= 7 && *str <= 13) || *str == '\e')
			ft_push(buf, '\\');
		ft_push(buf, *str++);
	}
	if (f->flags & F_MINUS)
		ft_print_width(buf, &f->width, ' ');
}

void	ft_reset_opt_k(t_options *f)
{
	f->flags = 0;
	f->width = -1;
	f->sum = 2;
	f->base = 10;
}

void	ft_k_print(t_options *f, t_buff *buf, unsigned long long unum)
{
	int	sec;
	int	minutes;
	int	hours;

	sec = unum % 60;
	unum /= 60;
	minutes = unum % 60;
	unum /= 60;
	hours = unum;
	ft_reset_opt_k(f);
	if (hours)
		ft_di_print(f, buf, hours);
	if (minutes || hours)
	{
		if (hours)
			ft_push(buf, ':');
		ft_di_print(f, buf, minutes);
	}
	if (sec || minutes || hours)
	{
		if (minutes || hours)
			ft_push(buf, ':');
		ft_di_print(f, buf, sec);
	}
}
