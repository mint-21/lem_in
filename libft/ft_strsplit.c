/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:04:09 by vfearles          #+#    #+#             */
/*   Updated: 2021/05/06 14:04:09 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_wordnew(char *word, char c)
{
	char		*slovo;

	slovo = word;
	while (*word && *word != c)
		word++;
	*word = '\0';
	return (ft_strdup(slovo));
}

static void	ft_free(char **result, size_t i)
{
	while (i--)
		ft_strdel(&(result[i]));
	free(*result);
}

static char	**ft_newstr(char *str, char c, size_t count, size_t i)
{
	char		**result;
	char		*word;

	result = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	if (result)
	{
		while (i < count)
		{
			while (*str == c)
				str++;
			if (*str)
			{
				word = ft_wordnew(str, c);
				if (!(word))
				{
					ft_free(result, i);
					return (NULL);
				}
				result[i++] = word;
				str += (ft_strlen(word) + 1);
			}
		}
		result[i] = NULL;
	}
	return (result);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**words;
	char	*line;

	line = ft_strdup((char *)s);
	if (!s || !(line))
		return (NULL);
	words = ft_newstr(line, c, ft_count(line, c), 0);
	free(line);
	return (words);
}
