/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_turns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:59:54 by asmall            #+#    #+#             */
/*   Updated: 2020/09/22 12:03:20 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualise.h"

t_turns		*make_new_ant_turn(void)
{
	t_turns	*t;

	t = (t_turns *)malloc(sizeof(t_turns));
	t->ant_and_room = NULL;
	t->next = NULL;
	return (t);
}

int			count_amount_turns(char *line)
{
	int		i;
	int		amount_turns;

	i = -1;
	amount_turns = 1;
	while (line[++i] != '\0' && line[i])
		if (line[i] == ' ')
			amount_turns++;
	return (amount_turns);
}

void		free_turn(t_turns *start, t_turns *curr)
{
	while (curr)
	{
		free(curr->ant_and_room);
		start = curr;
		curr = curr->next;
		free(start);
	}
	free(curr);
}

void		turn_vis_ants(int amount_turns, char **turns,
				char ant_num_str[4], t_vis_ants **array)
{
	int		i;
	t_turns	*start;
	t_turns	*curr;

	i = -1;
	start = make_new_ant_turn();
	curr = start;
	while (++i < amount_turns + 1)
	{
		curr->ant_and_room = ft_strsplit(turns[i], '-');
		curr->next = make_new_ant_turn();
		curr = curr->next;
	}
	curr = start;
	while (curr && curr->ant_and_room)
	{
		i = 0;
		while (++i < (int)ft_strlen(curr->ant_and_room[0]))
			ant_num_str[i - 1] = curr->ant_and_room[0][i];
		(*array)[ft_atoi(ant_num_str) - 1].next_name = curr->ant_and_room[1];
		curr = curr->next;
	}
	curr = start;
	free_turn(curr, start);
}

bool		parse_turns_line(t_vis_ants **array, t_data **g_s)
{
	char	**turns;
	char	**temp_str;
	int		amount_turns;
	int		i;
	char	ant_num_str[4];

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
		(*array)[ft_atoi(ant_num_str) - 1].next_name = temp_str[1];
	}
	(*g_s)->step += 1;
	return (false);
}
