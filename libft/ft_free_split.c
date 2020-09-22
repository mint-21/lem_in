/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:09:52 by asmall            #+#    #+#             */
/*   Updated: 2019/11/06 14:09:52 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_split_free(char **str_split)
{
	size_t		i;

	i = 0;
	while (str_split[i] != NULL)
	{
		free(str_split[i]);
		i++;
	}
	free(str_split);
	return (NULL);
}
