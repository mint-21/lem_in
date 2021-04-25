/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:36:06 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 15:36:58 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[k + i])
	{
		while (needle[j] == haystack[k + i] && k + i < len)
		{
			j++;
			i++;
			if (needle[j] == '\0')
				return ((char *)&haystack[k + i - j]);
		}
		j = 0;
		i = 0;
		k++;
	}
	return (NULL);
}
