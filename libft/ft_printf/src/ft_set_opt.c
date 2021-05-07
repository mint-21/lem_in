/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 14:48:36 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/26 14:48:38 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_set_flags(const char **form, t_options *f)
{
	while (**form)
	{
		if (**form == '-')
			f->flags |= F_MINUS;
		else if (**form == '+')
			f->flags |= F_PLUS;
		else if (**form == ' ')
			f->flags |= F_SP;
		else if (**form == '#')
			f->flags |= F_SHARP;
		else if (**form == '0')
			f->flags |= F_NULL;
		else
			break ;
		(*form)++;
	}
}

void	ft_set_width(const char **form, t_options *f, va_list ap)
{
	if (**form >= '0' && **form <= '9')
	{
		f->width = ft_atoi(*form);
		while ((**form) >= '0' && (**form) <= '9')
			(*form)++;
	}
	else if (**form == '*')
	{
		f->width = va_arg(ap, int);
		if (f->width < 0)
		{
			f->flags |= F_MINUS;
			f->width = -f->width;
		}
		(*form)++;
	}
}

void	ft_set_accur(const char **form, t_options *f, va_list ap)
{
	if (**form == '.')
	{
		(*form)++;
		if (**form >= '0' && **form <= '9')
		{
			f->sum = ft_atoi(*form);
			while ((**form) >= '0' && (**form) <= '9')
				(*form)++;
		}
		else if (**form == '*')
		{
			f->sum = va_arg(ap, int);
			(*form)++;
		}
		else
			f->sum = 0;
	}
}

int	ft_set_spec(char c, t_options *f)
{
	char	*nospec;

	nospec = "-+ #0*.hlLtzj";
	if (!(c >= '0' && c <= '9'))
	{
		while (*nospec)
		{
			if (c == *nospec)
				return (0);
			nospec++;
		}
		f->spec = c;
		return (1);
	}
	return (0);
}
