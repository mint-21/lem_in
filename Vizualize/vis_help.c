/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmebble <qmebble@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 20:13:54 by qmebble           #+#    #+#             */
/*   Updated: 2019/08/25 00:09:38 by qmebble          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

int			ft_find_max_x(t_data s)
{
	int		max;
	t_room	*current;

	max = -MAX_INT - 1;
	current = s.rooms;
	while (current)
	{
		if (current->x > max)
			max = current->x;
		current = current->next;
	}
	return (max);
}

int			ft_find_max_y(t_data s)
{
	int		max;
	t_room	*current;

	max = -MAX_INT - 1;
	current = s.rooms;
	while (current)
	{
		if (current->y > max)
			max = current->y;
		current = current->next;
	}
	return (max);
}

int			close_all(void)
{
	free(g_vis_rooms);
	SDL_DestroyWindow(g_main_window);
	g_main_window = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return (0);
}

void			null_ptr_ant(t_vis_ants *ant, int *null_count)
{
	(*ant).x_diff = 0;
	(*ant).y_diff = 0;
	(*ant).current_room = (*ant).next_room;
	(*ant).next_room_name = NULL;
	(*null_count)++;
}

t_vis_rooms	*make_new_vis_room(void)
{
	t_vis_rooms	*room;

	if (!(room = (t_vis_rooms *)malloc(sizeof(t_vis_rooms))))
		return (NULL);
	room->next = NULL;
	room->room.x = 0;
	room->room.y = 0;
	room->room.h = 50;
	room->room.w = 50;
	room->name = NULL;
	room->num = 0;
	return (room);
}
