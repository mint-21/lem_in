/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:04:09 by vfearles          #+#    #+#             */
/*   Updated: 2021/05/06 19:05:34 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	g(char const *s, char c)
{
	size_t			size;

	size = 0;
	while (*s == c)
		s++;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
		{
			size++;
			while (*s == c)
				s++;
		}
		if (*s != '\0')
			s++;
	}
	return (size + 1);
}

static char	**matrm(size_t number_of_strings)
{
	char			**array;
	int				i;

	array = (char **)malloc(sizeof(char *) * number_of_strings);
	if (!(array))
		return (NULL);
	i = 0;
	while (i < (int)number_of_strings)
		array[i++] = NULL;
	return (array);
}

static void	*matrdel(char **array)
{
	size_t			i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**array_procces(char const *s, char c, char **array)
{
	size_t			size;
	size_t			i;
	char			*str;

	i = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		size = ft_strlen(s);
		str = ft_strchr(s, c);
		str = ft_strchr(s, c);
		if (str != NULL)
			size = str - s;
		array[i] = (char *)ft_memalloc(sizeof(char) * (size + 1));
		if (!(array[i]))
			return (matrdel(array));
		ft_strncpy(array[i++], s, size);
		s = s + size;
		if (*s != '\0')
			s++;
	}
	return (array);
}

char	**ft_strsplit(char const *s, char c)
{
	char			**array;

	if (s == NULL)
		return (NULL);
	array = (char **)matrm(sizeof(char *) * (g(s, c) + 1));
	if (!(array))
		return (NULL);
	array_procces(s, c, array);
	return (array);
}
