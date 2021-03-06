/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:58:02 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/15 19:58:10 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_buf(char *buf, size_t *i, size_t buff_size, char c)
{
	if (*i == buff_size)
	{
		write(1, buf, *i);
		*i = 0;
	}
	buf[*i] = c;
	(*i)++;
}
