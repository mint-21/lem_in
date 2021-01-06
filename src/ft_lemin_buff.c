/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lemin_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:21:00 by asmall            #+#    #+#             */
/*   Updated: 2021/01/06 14:06:49 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_step_and_ant(char *name, int ants)
{
    int i;

    i = 0;
    while (i++ <= ants)
    {
        ft_printf("L%d-%s ", i, name);
        ft_printf("\n");
    }
}

void		ft_buff_lem(t_data *data)
{
	int		steps;

	steps = 0;
	if (data->ways->len == 2)
    {
	    print_step_and_ant(data->ways->path->next->room->name, data->ants);
        free_list(data->ways);
        return ;
    }
    fill_buf(data->ways);
    while (print_line(data->ways, ++steps))
        ft_printf("\n");
    free_list(data->ways);
}
