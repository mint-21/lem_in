/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 23:17:28 by asmall            #+#    #+#             */
/*   Updated: 2021/04/25 13:51:16 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bit_check(int flag, int position)
{
	return ((flag >> position) & 1);
}

void	ft_bit_on(int *flag, int position)
{
	*flag = *flag | (1 << position);
}

void	ft_bit_off(int *flag, int position)
{
	*flag = *flag & (~(1 << position));
}
