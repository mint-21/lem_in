/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff_lem_buff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 19:21:00 by asmall            #+#    #+#             */
/*   Updated: 2020/07/05 19:21:04 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** The function prints each step to the console
** ft_step: buffered the text one step per path
*/

void	teleport_all(char *name, int ants)
{
    int i;

    i = 1;
    while (i <= ants)
    {
        ft_printf("L%d-%s ", i, name);
        i++;
    }
    ft_printf("\n");
}

void		ft_buff_lem(t_data *data)
{
	int		steps;

	steps = 0;
	if (data->ways->len == 2)
    {
	    teleport_all(data->ways->path->next->room->name, data->ants);
        free_path_list(data->ways);
        return ;
    }
    fill_buf(data->ways);
    while (print_line(data->ways, ++steps))
        ft_printf("\n");
    free_path_list(data->ways);
}
