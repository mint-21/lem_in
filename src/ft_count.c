#include "lemin.h"

int	get_max_path(t_room *start, t_room *end)
{
	int			i;
	int			j;
	t_connect	*ptr;
	t_connect	*src;

	ptr = start->connects;
	src = end->connects;
	i = 0;
	j = 0;
	while (ptr || src)
	{
		if (ptr)
		{
			ptr = ptr->next;
			i++;
		}
		else if (src)
		{
			src = src->next;
			j++;
		}
	}
	return ((j < i) ? j : i);
}
