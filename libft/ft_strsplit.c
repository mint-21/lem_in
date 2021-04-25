/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:04:09 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/25 16:12:15 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_count(char const *s, char c)
{
	size_t	n;

	if (!s)
		return (0);
	n = 0;
	while (*s == c)
		++s;
	while (*s)
	{
		while (*s && *s != c)
			++s;
		++n;
		while (*s == c)
			++s;
	}
	return (n);
}

static char	**clean(char **arr, size_t n)
{
	while (n--)
		free(arr[n]);
	free(arr);
	return (NULL);
}

char	**ft_strsplit(char const *s, char c)
{
	const char	*t;
	char		**arr;
	size_t		n;
	size_t		i;

	n = ft_word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (n + 1));
	if (!s || !(arr))
		return (NULL);
	i = 0;
	while (*s == c)
		++s;
	while (i < n)
	{
		t = s;
		while (*s && *s != c)
			++s;
		arr[i] = (char *)malloc(s - t + 1);
		if (!(arr[i]))
			return (clean(arr, i));
		ft_strncpy(arr[i], t, s - t);
		arr[i++][s - t] = '\0';
		while (*s == c)
			++s;
	}
	arr[i] = NULL;
	return (arr);
}
