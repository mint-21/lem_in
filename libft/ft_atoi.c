/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:30:19 by asmall            #+#    #+#             */
/*   Updated: 2019/04/17 17:52:32 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				prov(const char *str, int i, int flag)
{
	unsigned long long	n;

	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n *= 10;
		n += str[i] - '0';
		if (n > 9223372036854775807)
		{
			if (flag == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	if ((n > 2147483648 && flag == -1) || (n > 2147483647 && flag == 1))
		return (0);
	return (n * flag);
}

int						ft_atoi(const char *str)
{
	int					i;
	int					flag;

	i = 0;
	flag = 1;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag = -1;
		i++;
	}
	return (prov(str, i, flag));
}
