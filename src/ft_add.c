#include "lemin.h"

t_rooms *b_find(t_room *r, t_rooms *buf)
{
	while (buf)
	{
		if (buf->r == r)
			 break ;
		buf = buf->next;
	}
	return (buf);
}

t_rooms *add_to_buf(t_room *r, t_rooms *buf)
{
	t_rooms	*new;

	if (b_find(r, buf))
		return (buf);
	if (!(new = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
		exit(1);
	new->next = buf;
	new->prev = NULL;
	new->r = r;
	return (new);
}

void q_insert(t_rooms *q, t_rooms *new)
{
	while (q->next && q->r->weight <= new->r->weight)
		q = q->next;
	if (!q->next && q->r->weight <= new->r->weight)
	{
		q->next = new;
		new->prev = q;
	}
	else
	{
		if (q->prev)
			q->prev->next = new;
		new->prev = q->prev;
		new->next = q;
		q->prev = new;
	}
}

void q_add_link(t_rooms **q, t_connect *l, t_room *par)
{
	t_rooms	*new;

	while (l)
	{
		if (l->room->weight == INF)
		{
			l->room->weight = par->weight + l->weight;
			l->room->room_par = par;
			if (!(new = (t_rooms *)ft_memalloc(sizeof(t_rooms))))
				exit(1);
			new->r = l->room;
			if (!*q || l->room->weight < (*q)->r->weight)
			{
				if (*q)
					(*q)->prev = new;
				new->next = *q;
				*q = new;
			}
			else
				q_insert(*q, new);
		}
		l = l->next;
	}
}
