/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:23:30 by asmall            #+#    #+#             */
/*   Updated: 2020/04/27 19:48:01 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

void			free_text(char **text, char **temp)
{
	free(*text);
	*text = *temp;
}

int				set_line(char **text, char **line, char *ptr, const int fd)
{
	char		*temp;

	if (ft_strlen(text[fd]) != 0)
	{
		if (!(ft_strchr(text[fd], '\n')))
		{
			*line = ft_strdup(text[fd]);
			ft_strdel(&text[fd]);
			return (1);
		}
		*ptr = '\0';
		temp = ft_strdup(ptr + 1);
		*line = ft_strdup(text[fd]);
		free_text(&text[fd], &temp);
	}
	else
		return (0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*text[FD_MAX];
	char		*temp;
	char		*ptr;
	int			len;

	temp = NULL;
	if (fd > FD_MAX || fd < 0 || !line || BUFF_SIZE < 0 || read(fd, buf, 0) < 0)
		return (-1);
	if (text[fd] == NULL)
		text[fd] = ft_strnew(1);
	while ((ptr = ft_strchr(text[fd], '\n')) == NULL)
	{
		if ((len = read(fd, buf, BUFF_SIZE)) == 0)
			break ;
		buf[len] = '\0';
		temp = ft_strjoin(text[fd], buf);
		free_text(&text[fd], &temp);
	}
	return (set_line(text, line, ptr, fd));
}
