/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:09:52 by vfearles          #+#    #+#             */
/*   Updated: 2019/11/06 14:09:52 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	*ft_free_str_split(char **str_split)
{
	size_t			i;

	i = 0;
	while (str_split[i] != NULL)
	{
		free(str_split[i]);
		i++;
	}
	free(str_split);
	return (NULL);
}
