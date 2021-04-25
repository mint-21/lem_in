/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:44:48 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 14:42:56 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_buf(char *buf, size_t *i, size_t buff_size, char *str)
{
	size_t	j;

	j = 0;
	while (str[j])
	{
		ft_putchar_buf(buf, i, buff_size, str[j]);
		++j;
	}
}
