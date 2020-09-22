/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_turns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:59:54 by asmall            #+#    #+#             */
/*   Updated: 2020/09/21 12:59:57 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

t_vis_ants			*make_new_vis_ants_array(t_data s)
{
	t_vis_ants		*array;
	t_vis_rooms		*current;
	int				i;

	array = (t_vis_ants *)malloc(sizeof(t_vis_ants) * s.ants);
	current = g_vis_rooms;
	while (current && current->num != s.start->n)
		current = current->next;
	i = -1;
	while (++i < s.ants)
	{
		array[i].current_room = current->room;
		array[i].next_room.h = 50;
		array[i].next_room.w = 50;
		array[i].next_room.x = 0;
		array[i].next_room.y = 0;
		array[i].x_diff = 0;
		array[i].y_diff = 0;
		array[i].current_room_name = current->name;
		array[i].next_room_name = NULL;
	}
	return (array);
}

t_turns_parser		*make_new_ant_turn(void)
{
	t_turns_parser	*t;

	t = (t_turns_parser *)malloc(sizeof(t_turns_parser));
	t->ant_and_room = NULL;
	t->next = NULL;
	return (t);
}

int					count_amount_turns(char *line)
{
	int				i;
	int				amount_turns;

	i = -1;
	amount_turns = 1;
	while (line[++i] != '\0' && line[i])
		if (line[i] == ' ')
			amount_turns++;
	return (amount_turns);
}

void				turn_vis_ants(int amount_turns, char **turns,
						char ant_num_str[4], t_vis_ants **array)
{
	int				i;
	t_turns_parser	*start;
	t_turns_parser	*current;

	i = -1;
	start = make_new_ant_turn();
	current = start;
	while (++i < amount_turns + 1)
	{
		current->ant_and_room = ft_strsplit(turns[i], '-');
		current->next = make_new_ant_turn();
		current = current->next;
	}
	current = start;
	while (current && current->ant_and_room)
	{
		i = 0;
		while (++i < (int)ft_strlen(current->ant_and_room[0]))
			ant_num_str[i - 1] = current->ant_and_room[0][i];
		(*array)[ft_atoi(ant_num_str) - 1].next_room_name = current->ant_and_room[1];
		current = current->next;
	}
	current = start;
	while (current)
	{
		free(current->ant_and_room);
		start = current;
		current = current->next;
		free(start);
	}
	free(current);
}

bool				parse_turns_line(t_vis_ants **array, t_data **g_s)
{
	char			**turns;
	char			**temp_str;
	int				amount_turns;
	int				i;
	char			ant_num_str[4];

	turns = NULL;
	amount_turns = count_amount_turns((*g_s)->split[(*g_s)->step]);
	if (amount_turns)
		turns = ft_strsplit((*g_s)->split[(*g_s)->step], ' ');
	if (turns)
		turn_vis_ants(amount_turns, turns, ant_num_str, array);
	else
	{
		i = 0;
		temp_str = ft_strsplit((*g_s)->map_data, '-');
		while (++i < (int)ft_strlen(temp_str[0]))
			ant_num_str[i - 1] = temp_str[0][i];
		(*array)[ft_atoi(ant_num_str) - 1].next_room_name = temp_str[1];
	}
	(*g_s)->step += 1;
	return (false);
}
