/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_card.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 18:30:08 by vfearles          #+#    #+#             */
/*   Updated: 2020/05/22 19:33:49 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char		*ft_read_line(char *str, int fd)
{
	int		ret;
	char	*temp;
	char	line[16002];

	ft_bzero(line, 16001);
	while ((ret = read(fd, line, 16001)) > 0)
	{
		line[ret] = '\0';
		temp = str;
		if (!(str = ft_strjoin(str, line)))
			ft_perror();
		free(temp);
	}
	(ret < 0) ? ft_perror() : 1;
	return (str);
}

/*
** Главная функция чтения карты.
** ft_read_line: чтени карты через read в строку.
*/

char		*reading_card(t_flags *flags, char ***str_split)
{
	char	*str;
	char	*trash;
	int		fd;
	char	*ptr;

	fd = (flags->fd_path) ? open(flags->fd_path, O_RDONLY) : 0;
	(fd < 0) ? ft_perror() : 1;
	str = (char *)malloc(1);
	ft_bzero(str, 1);
	str = ft_read_line(str, fd);
	if (fd > 2)
		((close(fd)) < 0) ? ft_perror() : 1;
	if (!(trash = ft_strdup(str)))
		ft_perror();
	ptr = str;
	while (*str++)
		if (*str == '\n' && *(str + 1) == '\n')
			ft_print_error(E_MALLOC);
	*str_split = ft_strsplit(trash, '\n');
	str = ptr;
	ft_strdel(&str);
	return (trash);
}
