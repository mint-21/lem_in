/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 22:14:00 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 15:39:09 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		while (needle[j] == haystack[k + i])
		{
			j++;
			k++;
			if (needle[j] == '\0')
				return ((char *)&haystack[k + i - j]);
		}
		j = 0;
		k = 0;
		i++;
	}
	return (NULL);
}
