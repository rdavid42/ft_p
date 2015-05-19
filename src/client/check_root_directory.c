/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_root_directory.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 12:52:00 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 12:53:56 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int						check_root_directory(char *root)
{
	DIR					*dir;

	if (!(dir = opendir(root)))
	{
		if (mkdir(root, 0755) == -1)
		{
			(void)!write(1, "Failed to recreate current directory!\n", 38);
			return (0);
		}
		(void)!chdir(root);
		(void)!write(1, "Current directory recreated!\n", 29);
		return (1);
	}
	closedir(dir);
	return (1);
}
