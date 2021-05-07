/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_card_reading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 11:17:02 by vfearles          #+#    #+#             */
/*   Updated: 2021/04/17 14:31:49 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char	*ft_read_line(char *str, int fd)
{
	int		ret;
	char	*temp;
	char	line[16002];

	ft_bzero(line, 16001);
	ret = read(fd, line, 16001);
	while (ret > 0)
	{
		line[ret] = '\0';
		temp = str;
		str = ft_strjoin(str, line);
		if (!str)
			ft_perror();
		free(temp);
		ret = read(fd, line, 16001);
	}
	if (ret < 0)
		ft_perror();
	return (str);
}

char	*reading_card(char ***str_split, int fd)
{
	char	*str;
	char	*trash;
	char	*ptr;

	str = (char *)malloc(1);
	ft_bzero(str, 1);
	str = ft_read_line(str, fd);
	if (fd > 2)
	{
		if ((close(fd)) < 0)
			ft_perror();
	}
	trash = ft_strdup(str);
	if (!trash)
		ft_perror();
	ptr = str;
	while (*str++)
		if (*str == '\n' && *(str + 1) == '\n')
			ft_print_error(E_NO_CORRECT);
	*str_split = ft_strsplit(trash, '\n');
	str = ptr;
	ft_strdel(&str);
	return (trash);
}
