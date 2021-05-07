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

void	ft_help_set(const char **form, t_options *f)
{
	if (**form == 't')
	{
		if (f->length < LEN_TIME)
			f->length = LEN_TIME;
		else
			f->length = f->length;
	}
	else if (**form == 'z')
	{
		if (f->length < LEN_Z)
			f->length = LEN_Z;
		else
			f->length = f->length;
	}
	else if (**form == 'j')
	{
		if (f->length < LEN_J)
			f->length = LEN_J;
		else
			f->length = f->length;
	}
}

void	ft_set_mod_hh_ll(const char **form, t_options *f)
{
	if ((**form == 'h' && f->length != LEN_HH))
	{
		if (f->length < LEN_H)
			f->length = LEN_H;
		else
			f->length = f->length;
	}
	else if (**form == 'l' && f->length != LEN_LL)
	{
		if (f->length < LEN_L)
			f->length = LEN_L;
		else
			f->length = f->length;
	}
}

void	ft_set_modif_l(t_options *f)
{
	if (f->length < LEN_LL)
		f->length = LEN_LL;
	else
		f->length = f->length;
}

void	ft_set_modif(const char **form, t_options *f)
{
	while (**form)
	{
		if (**form == 'h' && *(*form + 1) == 'h' && (*form)++)
		{
			if (f->length < LEN_HH)
				f->length = LEN_HH;
			else
				f->length = f->length;
		}
		else if (**form == 'l' && *(*form + 1) == 'l' && (*form)++)
			ft_set_modif_l(f);
		else if ((**form == 'h' && f->length != LEN_HH) || (**form == 'l'
				&& f->length != LEN_LL))
			ft_set_mod_hh_ll(form, f);
		else if (**form == 'L')
			ft_set_modif_l(f);
		else if (**form == 't' || **form == 'z' || **form == 'j')
			ft_help_set(form, f);
		else
			break ;
		(*form)++;
	}
}
