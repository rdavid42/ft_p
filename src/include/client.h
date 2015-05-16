#ifndef CLIENT_H
# define CLIENT_H

# define CMDS			6

typedef struct			s_cmd
{
	int					len;
	char const			*name;
	void				(*interpret)(int *, char *cmd);
}						t_cmd;

void					usage(char *s);

#endif