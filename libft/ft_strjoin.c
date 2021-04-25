/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:18:31 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 15:33:19 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;

	if (s1 && s2)
	{
		r = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (r)
			return (ft_strcat(ft_strcpy(r, s1), s2));
	}
	return (NULL);
}
