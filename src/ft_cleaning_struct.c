/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaning_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfearles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:41:51 by vfearles          #+#    #+#             */
/*   Updated: 2020/10/08 18:41:53 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_free_connects(t_connect *connects)
{
	t_connect	*tmp;

	while (connects)
	{
		tmp = connects;
		connects = connects->next;
		free(tmp);
	}
}

static void		ft_free_path(t_path *path)
{
	t_path		*tmp;

	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

static void		ft_free_ways(t_way *way)
{
	t_way		*tmp;

	while (way)
	{
		tmp = way;
		way = way->next;
		ft_free_path(tmp->path);
		free(tmp);
	}
}

static void		ft_free_vars(t_option *options)
{
	t_option	*tmp;

	while (options)
	{
		tmp = options;
		options = options->next;
		ft_free_ways(tmp->ways);
		free(tmp);
	}
}

/*
** Cleaning up the main structure
*/

void			ft_struct_free(t_data *data)
{
	t_room		*tmp;

	if (data->rooms)
		while (data->rooms)
		{
			tmp = data->rooms;
			data->rooms = data->rooms->next;
			free(tmp->name);
			ft_free_connects(tmp->connects);
			if (tmp->out_part)
			{
				free(tmp->out_part->name);
				ft_free_connects(tmp->out_part->connects);
			}
			free(tmp->out_part);
			free(tmp);
		}
	(data->links) ? (ft_clean_links(data)) : 0;
	(data->ways_dij) ? (ft_free_ways(data->ways_dij)) : 0;
	(data->options) ? (ft_free_vars(data->options)) : 0;
}
