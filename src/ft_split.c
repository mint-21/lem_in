#include "lemin.h"

void	add_link2(t_connect **l, t_room *dst, int weight)
{
	t_connect *new;
	if (!(new = (t_connect *)ft_memalloc(sizeof(t_connect))))
		exit(1);
	new->next = *l;
	*l = new;
	new->room = dst;
	new->weight = weight;
}

void	split(t_way *way)
{
	t_path	*p;
	t_room	*out;

	while (way)
	{
		p = way->path->next;
		while (p->next)
		{
			if (!(out = (t_room *)ft_memalloc(sizeof(t_room))))
				exit(1);
			out->weight = INF;
			out->connects = p->room->connects;
			p->room->connects = NULL;
			add_link2(&out->connects, p->room, 0);
			add_link2(&p->room->connects, p->prev->room->out_part == NULL ?
				p->prev->room : p->prev->room->out_part, -1);
			p->room->out_part = out;
			out->in_part = p->room;
			p = p->next;
		}
		way = way->next;
	}
}
