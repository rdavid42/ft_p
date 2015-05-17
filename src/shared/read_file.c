
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
		return (print_error("Could not open file !\n", -1));
	count = 0;
	while ((ret = read(fd, buf, READ_BUFS)) != 0)
	{
		if (ret == -1)
		{
			close(fd);
			return (print_error("Could not read file !\n", -1));
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

char			*read_file(char const *filename)
{
	int			size;
	int			fd;
	int			i[2];
	char		buf[READ_BUFS];
	char		*file;

	if ((size = file_size(filename)) == -1)
		return (print_error_p("Could not get file size !\n"));
	if (!(file = (char *)malloc(sizeof(char) * size + 1)))
		return (print_error_p("Could not allocate memory !\n"));
	if ((fd = open(filename, O_RDONLY, 0644)) == -1)
		return (print_error_p("Could not open file !\n"));
	i[1] = 0;
	while ((i[0] = read(fd, buf, READ_BUFS)) != 0)
	{
		if (i[0] == -1)
		{
			close(fd);
			return (print_error_p("Could not read file !\n"));
		}
		copy_file_chunk(file, buf, &i[0], &i[1]);
	}
	file[i[1]] = '\0';
	close(fd);
	return (file);
}
