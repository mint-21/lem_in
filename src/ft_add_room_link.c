/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_room_link.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 17:30:42 by asmall            #+#    #+#             */
/*   Updated: 2020/08/20 11:42:51 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		find_name_num(char *str, t_room *r)
{
	t_room *tmp;

	tmp = r;
	while (str && tmp)
	{
		if (ft_strncmp(str, tmp->name, ft_strlen_char(str, "-")) == 0)
			return (tmp->n);
		tmp = tmp->next;
	}
	return (-1);
}

int		add_link_list(t_link **link)
{
	t_link	*tmp;
	t_link	*list;

	tmp = NULL;
	if (!(tmp = (t_link*)malloc(sizeof(t_link))))
		return (-1);
	tmp->next = NULL;
	list = *link;
	tmp->next = list;
	*link = tmp;
	return (0);
}

int	fill_link(t_data *s, int n_a, int n_b)
{
	t_link *tmp;

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

int	add_link(t_data *s, char *tab)
{
	int n_a;
	int n_b;
	int stat;

	if (!s->links)
	{
		if (!(s->links = (t_link **)malloc(sizeof(t_link *) * s->rooms_count)))
			return (-1);
		ft_bzero(s->links, sizeof(t_link *) * s->rooms_count);
	}
	if (!tab[0] || !tab[1] || !tab[2])
		return (-2);
	if ((n_a = find_name_num(tab, s->rooms)) == -1)
		return (-2);
	while (tab && *tab != '-')
		tab++;
	tab += 1;
	if ((n_b = find_name_num(tab, s->rooms)) == -1 || n_a == n_b)
		return (-2);
	if ((stat = fill_link(s, n_a, n_b)) == -2 || stat == -2)
		return (stat);
	return (3);
}
