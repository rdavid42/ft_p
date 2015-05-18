/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 16:31:00 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 17:43:37 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <stddef.h>

# define OPEN_ERR			("ERROR: failed to open file!\n")
# define FILE_EXIST			("ERROR: file already exists!\n")
# define REC_ERR			("ERROR: failed to receive data!\n")
# define CO_CLOSED			("ERROR: connexion closed!\n")
# define FILE_NOT_FOUND		("ERROR: file not found!\n")
# define PERM_DENIED		("ERROR: permission denied!\n")

# define READ_BUFS			(16384)
# define BUFS				(16384)
# define GET_BUFS			(512)

int				slen(char const *s);
int				error(char const *msg);
char			*clean_line(char *old);
void			usage(char *s);
int				scmp(const char *s1, const char *s2, size_t n);
char			*ssub(char const *s, unsigned int start, size_t len);
char			**ssplit(char const *s, char c);
int				alen(char **array);
void			afree(char **array);
int				print_error(char const *msg, int const code);
void			*print_error_p(char const *msg);
char			*read_file(char const *filename, int *len);
int				stoi(const char *str);
void			err_msg(char const *msg);
char			*sjoin(char const *s, char const *s2);

#endif
