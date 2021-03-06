/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 16:38:52 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/25 14:23:01 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getlen(int n)
{
	size_t			i;

	i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	unsigned int	temp;

	len = ft_getlen(n);
	temp = n;
	if (n < 0)
	{
		temp = -n;
		len++;
	}
	str = ft_strnew(len + 1);
	if (!(str))
		return (NULL);
	str[--len] = temp % 10 + '0';
	while (temp)
	{
		temp /= 10;
		str[--len] = (temp % 10) + '0';
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
