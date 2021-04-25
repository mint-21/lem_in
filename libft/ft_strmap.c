/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:16:25 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 15:36:08 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*r;
	size_t	i;

	i = 0;
	r = ft_strnew(ft_strlen(s));
	if (s && f && r)
	{
		while (s[i])
		{
			r[i] = f(s[i]);
			i++;
		}
		return (r);
	}
	return (NULL);
}
