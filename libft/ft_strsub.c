/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:59:12 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/25 15:39:13 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*a;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
		i++;
	a = (char *)malloc(sizeof(char) * (len + 1));
	if (start > i || !a || len > i)
		return (NULL);
	i = start;
	start = 0;
	while (start < len)
	{
		a[j] = s[i];
		j++;
		i++;
		start++;
	}
	a[j] = '\0';
	return (a);
}
