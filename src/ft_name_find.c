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
** name_connect[i]: the name of the room before the '-' sign.
*/

int			ft_name_equ_room1(char *name_room, char *name_connect)
{
	int		i;

	i = -1;
	while (name_room[++i] && name_connect[i] && name_connect[i] != '-')
		if (name_room[i] != name_connect[i])
			return (0);
	if (name_room[i] == '\0' && name_connect[i] == '-')
		return (1);
	return (0);
}

/*
** The connection after the '-' sign with the name of the room is checked.
** name_connect[j]: the name of the room after the '-' sign.
*/

int			ft_name_equ_room2(char *name_room, char *name_connect)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (name_connect[j] && name_connect[j] != '-')
		++j;
	++j;
	while (name_room[i] && name_connect[j])
	{
		if (name_room[i] != name_connect[j])
			return (0);
		++i;
		++j;
	}
	if (name_room[i] == '\0' && name_connect[j] == '\0')
		return (1);
	return (0);
}

/*
** Search for room connections.
** head: the first room in the t_room structure.
*/

int			ft_findrooms(t_data *data, char *connect_str,
				t_room **room1, t_room **room2)
{
	t_room	*head;

	if (!room1 || !room2)
		ft_perror();
	head = data->rooms;
	while (head && (!(*room1) || !(*room2)))
	{
		if (!(*room1) && ft_name_equ_room1(head->name, &connect_str[0]))
			*room1 = head;
		else if (!(*room2) && ft_name_equ_room2(head->name, connect_str))
			*room2 = head;
		head = head->next;
	}
	if (!(*room1) || !(*room2))
		ft_print_error(E_NO_CORRECT);
	return (0);
}
