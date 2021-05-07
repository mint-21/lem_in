/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaning_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:41:51 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/17 14:34:56 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_free_connects(t_connect *connects)
{
	t_connect	*tmp;

	while (connects)
	{
		tmp = connects;
		connects = connects->next;
		free(tmp);
	}
}

static void	ft_free_ways(t_way *way)
{
	t_way		*tmp;
	t_path		*ptr;

	while (way)
	{
		tmp = way;
		way = way->next;
		while (tmp->path)
		{
			ptr = tmp->path;
			tmp->path = tmp->path->next;
			free(ptr);
		}
		free(tmp);
	}
}

static void	ft_free_vars(t_option *options)
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

void	ft_clean_links(t_data *s)
{
	t_link		*cur_l;
	t_link		*next_l;
	int			i;

	i = -1;
	while (++i < s->rooms_count)
	{
		cur_l = s->links[i];
		while (cur_l)
		{
			next_l = cur_l->next;
			free(cur_l);
			cur_l = next_l;
		}
	}
	free(s->links);
}

/*
** Cleaning up the main structure
*/

void	ft_struct_free(t_data *data)
{
	t_room		*tmp;

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
	if (data->links)
		ft_clean_links(data);
	if (data->options)
		ft_free_vars(data->options);
}
