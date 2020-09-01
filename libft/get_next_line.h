/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <asmall@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:30:00 by vfearles          #+#    #+#             */
/*   Updated: 2020/04/27 19:51:36 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10
# define FD_MAX 4096

# include "fcntl.h"
# include "sys/types.h"
# include "unistd.h"
# include "stdlib.h"
# include "libft.h"

void	free_text(char **text, char **temp);
int		get_next_line(const int fd, char **line);
int		set_line(char **text, char **line, char *ptr, const int fd);

#endif
