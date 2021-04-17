#include "lemin.h"

t_path	*p_copy(t_path *p)
{
	t_path	*tmp;
	t_path	*new;

	new = NULL;
	while (p->next)
		p = p->next;
	while (p)
	{
		if (!(tmp = (t_path *)ft_memalloc(sizeof(t_path))))
			exit(1);
		tmp->room = p->room;
		tmp->next = new;
		if (new)
			new->prev = tmp;
		new = tmp;
		p = p->prev;
	}
	return (new);
}

t_way 	*lst_copy(t_way *l)
{
	t_way	*new;
	t_way	*tmp;

	new = NULL;
	while (l->next)
		l = l->next;
	while (l)
	{
		if (!(tmp = (t_way *)ft_memalloc(sizeof(t_way))))
			exit(1);
		tmp->len = l->len;
		tmp->path = p_copy(l->path);
		tmp->ants = l->ants;
		tmp->next = new;
		if (new)
			new->prev = tmp;
		new = tmp;
		l = l->prev;
	}
	return (new);
}
