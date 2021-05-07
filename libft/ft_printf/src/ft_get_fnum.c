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

void	ft_help_get(t_fnum *fnum, char *ipoint, char *fpoint)
{
	if (fnum->ipoint)
		ipoint = fnum->ipoint;
	else
		ipoint = "0";
	if (fnum->fpoint)
		fpoint = fnum->fpoint;
	else
		fpoint = "0";
}

char	*ft_get_fnum(t_fnum *fnum, int sum, int ilen, t_options *f)
{
	char	*number;
	int		i;
	char	*ipoint;
	char	*fpoint;

	sum += 2;
	ipoint = NULL;
	fpoint = NULL;
	number = (char *)malloc(ilen + sum + 1);
	ft_help_get(fnum, ipoint, fpoint);
	i = 0;
	while (i < ilen)
		number[i++] = *ipoint++;
	number[i++] = '.';
	while (fnum->zero-- && (i < ilen + sum))
		number[i++] = '0';
	while (*fpoint && (i < ilen + sum))
		number[i++] = *fpoint++;
	while (i < ilen + sum)
		number[i++] = '0';
	ft_round(number, i - 1);
	if (sum == 2 && f->flags != 8 && f->flags != 9 && f->flags != 11
		&& f->flags != 13)
		number[i - 2] = '\0';
	return (number);
}
