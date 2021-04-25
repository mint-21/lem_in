/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:14:43 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 16:40:04 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst || !src)
		return (NULL);
	if (dst <= src)
	{
		while (len--)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (len--)
		{
			d[i] = s[i];
			i--;
		}
	}
	return (dst);
}
