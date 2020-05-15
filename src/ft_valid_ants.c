/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 15:52:39 by asmall            #+#    #+#             */
/*   Updated: 2020/04/27 21:06:50 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Повторение оригинальной функции atoi с исправленным выходом
** программы при возникновении ошибки или не валидности параметра
** количество муравьёв не должно быть отрицательным значением
*/

int				ft_atoi_mod(const char *str)
{
	long int	res;
	int			negative;

	negative = 1;
	res = 0;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	if (!*str)
		ft_print_error(E_ANT);
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	if (*str || !((res *= negative) >= INT_MIN && res <= INT_MAX))
		ft_print_error(E_INT);
	return ((int)res);
}

int				ft_valid_ants(char *str, t_data *data)
{
	if (!(*str == '+' || (*str <= '9' && *str >= '0')))
		ft_print_error(E_ANT);
	data->ants = ft_atoi_mod(str);
	data->v_flag = E_ANT;
	return (0);
}
