/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:28:23 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 15:02:49 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** reading_card: reading the map. ft_correct: card validation
** ft_find_all_ways: the main algorithm of the program
** print_n_free_map_data: printing the map to the console
** ft_buff_lem: output to the console of the program's response
*/

int	main(int ac, char **av)
{
	t_data	data;
	char	**str_split;
	char	*map_data;
	int		fd;

	fd = 0;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	data = ft_zerodata();
	map_data = reading_card(&str_split, fd);
	ft_correct(&data, &data.check, str_split);
	suurb(&data);
	print_n_free_map_data(&map_data);
	ft_buff_lem(&data, data.ways);
	ft_struct_free(&data);
	return (0);
}
