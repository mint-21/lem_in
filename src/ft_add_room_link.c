/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_room_link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:13:51 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/17 14:18:53 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	find_name_num(char *str, t_room *r)
{
	t_room	*tmp;

	tmp = r;
	while (str && tmp)
	{
		if (ft_strncmp(str, tmp->name, ft_strlen_char(str, "-")) == 0)
			return (tmp->n);
		tmp = tmp->next;
	}
	return (-1);
}

int	add_link_list(t_link **link)
{
	t_link	*tmp;
	t_link	*list;

	tmp = NULL;
	tmp = (t_link *)malloc(sizeof(t_link));
	if (!(tmp))
		return (-1);
	tmp->next = NULL;
	list = *link;
	tmp->next = list;
	*link = tmp;
	return (0);
}

int	fill_link(t_data *s, int n_a, int n_b)
{
	t_link	*tmp;

	tmp = s->links[n_a];
	while (tmp)
	{
		if (tmp->pair == n_b)
			return (-2);
		tmp = tmp->next;
	}
	if (add_link_list(&(s->links[n_a])) == -1 ||\
	add_link_list(&(s->links[n_b])) == -1)
		return (-1);
	s->links[n_a]->pair = n_b;
	s->links[n_b]->pair = n_a;
	s->links_count++;
	return (0);
}

int	add_link_process(char *tab, t_data *s, int n_a)
{
	if (!tab[0] || !tab[1] || !tab[2])
		return (-2);
	n_a = find_name_num(tab, s->rooms);
	if (n_a == -1)
		return (-2);
	return (n_a);
}

int	add_link(t_data *s, char *tab)
{
	int		n_a;
	int		n_b;
	int		stat;

	if (!s->links)
	{
		s->links = (t_link **)malloc(sizeof(t_link *) * s->rooms_count);
		if (!(s->links))
			return (-1);
		ft_bzero(s->links, sizeof(t_link *) * s->rooms_count);
	}
	n_a = 0;
	add_link_process(tab, s, n_a);
	while (tab && *tab != '-')
		tab++;
	tab += 1;
	n_b = find_name_num(tab, s->rooms);
	if (n_b == -1 || n_a == n_b)
		return (-2);
	stat = fill_link(s, n_a, n_b);
	if (stat == -2 || stat == -2)
		return (stat);
	return (3);
}
