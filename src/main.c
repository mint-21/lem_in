/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 22:28:23 by asmall            #+#    #+#             */
/*   Updated: 2020/06/13 19:28:53 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** ft_flags_lemin: проверка на флаги.
** reading_card: чтение карты. ft_correct: валидация карты.
** ft_parse_data: создание комнат и связей между ними.
** ft_find_all_ways: главный алгоритм программы.
** print_n_free_map_data: печать карты на консоль.
** ft_lemin: вывод на консоль ответа программы.
** ft_struct_free: очистка структуры.
*/

int			main(int ac, char **av)
{
	t_data	data;
	char	**str_split;
	char	*map_data;

	data = ft_zerodata();
	ft_flags_lemin(&data.flags, ac, av);
	map_data = reading_card(&data.flags, &str_split);
	ft_correct(&data, &data.check, str_split);
	ft_find_all_ways(&data);
	print_n_free_map_data(&map_data);
	ft_lemin(&data);
	(data.flags.ways == 1) ? ft_print_ways(data.best_opt->ways,
			data.best_opt->steps) : 0;
	ft_struct_free(&data);
	return (0);
}
