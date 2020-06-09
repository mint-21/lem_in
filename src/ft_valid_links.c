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

void	ft_valid_links(char *str, t_data *data, int j)
{
	int	i;

	i = 0;
	if (data->v_flag == 12 && data->i_start != -1 && data->i_end != -1)
		data->v_flag += E_ROOM;
	while (str[i] && str[i] != '-' && str[i] != ' ')
		i++;
	if (str[i] == '-' && str[i + 1])
	{
		if (!data->i_links_start)
		{
			data->i_links_start = j;
			data->v_flag += E_LINK;
		}
		data->i_links_end = j;
		i++;
	}
	while (str[i] && str[i] != '-' && str[i] != ' ')
		i++;
	(str[i]) ? ft_print_error(E_LINK) : 1;
}
