/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:24:12 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 15:36:32 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*r;

	i = 0;
	r = ft_strnew(ft_strlen(s));
	if (s && f && r)
	{
		while (s[i])
		{
			r[i] = f(i, s[i]);
			i++;
		}
		return (r);
	}
	return (NULL);
}
