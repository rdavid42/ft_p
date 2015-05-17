#ifndef SHARED_H
# define SHARED_H

# define READ_BUFS		16384
# define BUFS			16384

# include <stddef.h>

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
char			*read_file(char const *filename);

#endif