/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_name_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:26:15 by asmall            #+#    #+#             */
/*   Updated: 2020/07/16 06:35:16 by vfearles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** The connection is checked up to the '-' sign with the name of the room.
** r_connect[i]: the name of the room before the '-' sign.
** The connection after the '-' sign with the name of the room is checked.
** r_connect[j]: the name of the room after the '-' sign.
*/

int			ft_find_link_name(char *r_name, char *r_connect, int flag)
{
	int		i;
	int		j;

	i = -1;
	if (flag == 1)
	{
		while (r_name[++i] && r_connect[i] && r_connect[i] != '-')
			if (r_name[i] != r_connect[i])
				return (0);
		if (r_name[i] == '\0' && r_connect[i] == '-')
			return (1);
	}
	else if (flag == 2)
	{
		j = 0;
		while (r_connect[j] && r_connect[j] != '-')
			++j;
		while (r_name[++i] & r_connect[++j])
			if (r_name[i] != r_connect[j])
				return (0);
		if (r_name[i] == '\0' && r_connect[j] == '\0')
			return (1);
	}
	return (0);
}

/*
** Search for room connections.
** head: the first room in the t_room structure.
*/

int			ft_check_room_link(t_data *data, char *connect_str,
				t_room **room1, t_room **room2)
{
	t_room	*head;

	if (!room1 || !room2)
		ft_perror();
	head = data->rooms;
	while (head && (!(*room1) || !(*room2)))
	{
		if (!(*room1) && ft_find_link_name(head->name, &connect_str[0], 1))
			*room1 = head;
		else if (!(*room2) && ft_find_link_name(head->name, connect_str, 2))
			*room2 = head;
		head = head->next;
	}
	if (!(*room1) || !(*room2))
		ft_print_error(E_NO_CORRECT);
	return (0);
}
