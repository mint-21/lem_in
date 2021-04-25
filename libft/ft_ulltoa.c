/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:42:03 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/25 15:40:25 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(unsigned long long n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_ulltoa(unsigned long long n)
{
	char	*r;
	int		i;

	i = ft_count(n);
	r = (char *)malloc(sizeof(char) * (i + 1));
	if (!(r))
		return (NULL);
	r[i--] = '\0';
	if (n == 0)
		r[i] = 48;
	while (n)
	{
		r[i--] = n % 10 + 48;
		n = n / 10;
	}
	return (r);
}
