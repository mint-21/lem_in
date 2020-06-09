/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_lemin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:58:17 by vfearles          #+#    #+#             */
/*   Updated: 2020/05/13 19:33:59 by asmall           ###   ########.fr       */
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
