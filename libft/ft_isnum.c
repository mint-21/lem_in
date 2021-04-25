/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 21:44:16 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/25 13:52:03 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] != c)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}
