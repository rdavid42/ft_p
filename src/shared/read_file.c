/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 15:16:30 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 17:53:19 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "shared.h"

static int		file_size(char const *filename)
{
	int			fd;
	int			ret;
	int			count;
	char		buf[READ_BUFS];

	if ((fd = open(filename, O_RDONLY, 0644)) == -1)
		return (print_error("Failed to open file !\n", -1));
	count = 0;
	while ((ret = read(fd, buf, READ_BUFS)) != 0)
	{
		if (ret == -1)
		{
			close(fd);
			return (print_error("Failed to read file !\n", -1));
		}
		count += ret;
	}
	close(fd);
	return (count);
}

void			copy_file_chunk(char *file, char *buf,
								int *size, int *offset)
{
	int			i;

	i = -1;
	while (++i < *size)
		file[*offset + i] = buf[i];
	*offset += *size;
}

char			*read_file(char const *filename, int *len)
{
	int			size;
	int			fd;
	int			i[2];
	char		buf[READ_BUFS];
	char		*file;

	if ((size = file_size(filename)) == -1)
		return (NULL);
	if (len != NULL)
		*len = size;
	if (!(file = (char *)malloc(sizeof(char) * size + 1)))
		return (print_error_p("Failed to allocate memory !\n"));
	if ((fd = open(filename, O_RDONLY, 0644)) == -1)
		return (print_error_p("Failed open file !\n"));
	i[1] = 0;
	while ((i[0] = read(fd, buf, READ_BUFS)) != 0)
	{
		if (i[0] == -1)
			return (close(fd), print_error_p("Failed to read file !\n"));
		copy_file_chunk(file, buf, &i[0], &i[1]);
	}
	return (file[i[1]] = '\0', close(fd), file);
}
