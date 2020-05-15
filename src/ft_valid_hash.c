/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddarell <ddarell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:48:31 by vfearles          #+#    #+#             */
/*   Updated: 2020/01/12 13:42:23 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	ft_valid_hash(t_data *data, char *str)
{
	if (ft_strequ(str, "##start"))
	{
		if (data->i_start || data->i_end == -1)
			ft_print_error(E_START);
		data->i_start = -1;
		data->v_flag += E_START;
	}
	else if (ft_strequ(str, "##end"))
	{
		if (data->i_end || data->i_start == -1)
			ft_print_error(E_END);
		data->i_end = -1;
		data->v_flag += E_END;
	}
	else if (*str == '#' && (data->i_start == -1 || data->i_end == -1))
		ft_print_error(E_HASH);
	return (0);
}
