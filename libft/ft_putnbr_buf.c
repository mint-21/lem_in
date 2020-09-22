/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 19:46:22 by asmall            #+#    #+#             */
/*   Updated: 2020/04/27 19:46:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_buf(char *buf, size_t *i, size_t buff_size, int num)
{
	if (num / 10)
		ft_putnbr_buf(buf, i, buff_size, num / 10);
	ft_putchar_buf(buf, i, buff_size, num % 10 + '0');
}
