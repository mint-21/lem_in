/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:30:19 by vfearles          #+#    #+#             */
/*   Updated: 2019/04/17 17:52:32 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	unsigned long int	r;
	int					i;
	int					s;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||\
			str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		s = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r >= 9223372036854775807 && s == 1)
			return (-1);
		else if (r > 9223372036854775807 && s == -1)
			return (0);
		i++;
	}
	return ((int)r * s);
}
