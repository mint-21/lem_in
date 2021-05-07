/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zerodata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 20:06:00 by asmall            #+#    #+#             */
/*   Updated: 2021/04/17 15:02:28 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_zerodata2(t_data *data)
{
	data->map_data = NULL;
	data->split = NULL;
	data->start = NULL;
	data->end = NULL;
	data->rooms = NULL;
	data->options = NULL;
	data->best_opt = NULL;
	data->ways = NULL;
	data->links = NULL;
}

t_data	ft_zerodata(void)
{
	t_data		data;

	data.ants = 0;
	data.step = 0;
	data.flag = 1;
	data.rooms_count = 0;
	data.total_ways = 0;
	data.links_count = 0;
	data.check.valid_flag = 0;
	data.check.li_room_begin = 0;
	data.check.li_room_finish = 0;
	data.check.li_connects_bigin = 0;
	data.check.li_connects_finish = 0;
	data.check.hash_start = 0;
	data.check.hash_end = 0;
	data.vis_quit = 0;
	data.vis_pause = 0;
	data.ant = 0;
	data.steps = 0;
	ft_zerodata2(&data);
	return (data);
}
