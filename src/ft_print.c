/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:28:23 by asmall            #+#    #+#             */
/*   Updated: 2021/01/09 16:58:22 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			ft_print_error(int id)
{
	write(2, "ERROR\n", 6);
	if (id == 1)
		ft_printf("{red}%s{eoc}\n", "memory problems");
	if (id == 2)
		ft_printf("{red}%s{eoc}\n", "using forbidden characters");
	if (id == 3)
		ft_printf("{red}%s{eoc}\n", "no start command or coordinates");
	if (id == 4)
		ft_printf("{red}%s{eoc}\n", "no end command or coordinates");
	if (id == 5)
		ft_printf("{red}%s{eoc}\n", "ants parameter not valid");
	if (id == 6)
		ft_printf("{red}%s{eoc}\n", "room connections are not valid");
	if (id == 7)
		ft_printf("{red}%s{eoc}\n", "the card has no solution");
	if (id == 8)
		ft_printf("{red}%s{eoc}\n", "comments are not valid");
	if (id == 9)
		ft_printf("{red}%s{eoc}\n", "room names/coord are not valid");
	if (id == 10)
		ft_printf("{red}%s{eoc}\n", "room names/coord are duplicated");
	exit(id);
}

void	print_n_free_map_data(char **map_data)
{
	ft_printf("%s\n", *map_data);
	free(*map_data);
}

int		print_step(t_ants **buf, int step)
{
    t_ants *tmp;

    if (!*buf)
        return (0);
    tmp = *buf;
    while (tmp && step--)
    {
        tmp->curr = tmp->curr->next;
        ft_printf("L%d-%s ", tmp->num, tmp->curr->room->name);
        if (!tmp->curr->prev->prev)
            return (1);
        tmp = (!tmp->curr->next) ? buf_delete_ant(buf, tmp) : tmp->next;
    }
    return (1);
}
