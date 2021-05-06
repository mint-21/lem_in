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

void	ft_set_options(t_options *f, const char **form, va_list ap)
{
	char		*temp;

	f->flags = 0;
	f->width = -1;
	f->sum = -1;
	f->length = 0;
	f->base = 10;
	f->spec = 0;
	while (**form)
	{
		temp = (char *)*form;
		ft_set_flags(form, f);
		ft_set_width(form, f, ap);
		ft_set_accur(form, f, ap);
		ft_set_modif(form, f);
		if (ft_set_spec(**form, f) || temp == *form)
		{
			if (**form)
				(*form)++;
			break ;
		}
	}
}

int	ft_printf_help(va_list ap, t_buff buf)
{
	va_end(ap);
	if (buf.i)
		ft_fd_write(1, &buf);
	return (buf.len);
}

int	ft_printf(const char *form, ...)
{
	va_list		ap;
	t_options	f;
	t_buff		buf;

	f.color = 0;
	va_start(ap, form);
	ft_init_buff(&buf, 1);
	while (*form)
	{
		if (*form != '%')
		{
			if (!ft_color(&buf, &form, &f))
				ft_push(&buf, *form++);
		}
		else
		{
			form++;
			ft_set_options(&f, &form, ap);
			if (f.color)
				ft_put_color(&buf, &f);
			ft_handle_spec(&f, &buf, ap);
		}
	}
	return (ft_printf_help(ap, buf));
}

int	ft_dprintf_help(int fd, va_list ap, t_buff buf)
{
	va_end(ap);
	if (buf.i)
		ft_fd_write(fd, &buf);
	return (buf.len);
}

int	ft_dprintf(int fd, const char *form, ...)
{
	va_list		ap;
	t_options	f;
	t_buff		buf;

	va_start(ap, form);
	ft_init_buff(&buf, fd);
	while (*form)
	{
		if (*form != '%')
		{
			if (!ft_color(&buf, &form, &f))
				ft_push(&buf, *form++);
		}
		else
		{
			form++;
			ft_set_options(&f, &form, ap);
			if (f.color)
				ft_put_color(&buf, &f);
			ft_handle_spec(&f, &buf, ap);
		}
	}
	return (ft_dprintf_help(fd, ap, buf));
}
