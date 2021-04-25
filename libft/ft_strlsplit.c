/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:04:09 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/25 15:53:49 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdupl(const char *s, size_t len)
{
	size_t		i;
	char		*r;

	i = 0;
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (s && r)
	{
		while (i < len)
		{
			r[i] = s[i];
			i++;
		}
		r[len] = '\0';
		return (r);
	}
	return (NULL);
}

static t_list	*ft_createelem(const char *str, char c, size_t *i)
{
	size_t		f;
	char		*t;
	t_list		*r;

	f = *i;
	while (str[*i] && str[*i] != c)
		(*i)++;
	t = ft_strdupl(&str[f], *i - f);
	if (!(t))
		return (NULL);
	r = ft_lstnew(t, ft_strlen(t) + 1);
	free(t);
	return (r);
}

static size_t	ft_findword(char const *str, char c, size_t *i)
{
	while (str[*i] && str[*i] == c)
		(*i)++;
	if (str[*i] && str[*i] != c)
		return (*i);
	return (0);
}

static void	ft_del(void *content, size_t content_size)
{
	content_size = 0;
	content_size -= 1;
	free(content);
}

t_list	*ft_strlsplit(char const *s, char c)
{
	size_t		i;
	t_list		*l;
	t_list		*h;

	if (!s)
		return (NULL);
	i = 0;
	if (c == '\0')
		return (ft_createelem(s, c, &i));
	l = ft_createelem(s, c, &i);
	if (!((ft_findword(s, c, &i)) && l))
		return (NULL);
	h = l;
	while (s[i])
	{
		if (!(ft_findword(s, c, &i)))
			break ;
		l->next = ft_createelem(s, c, &i);
		if (!(l->next))
		{
			ft_lstdel(&h, &ft_del);
			return (NULL);
		}
		l = l->next;
	}
	return (h);
}
