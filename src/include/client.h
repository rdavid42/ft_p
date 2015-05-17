#ifndef CLIENT_H
# define CLIENT_H

# define REQ_ERR			("ERROR: failed to send request!\n")
# define REC_ERR			("ERROR: failed to receive data!\n")
# define CO_CLOSED			("ERROR: connexion closed!\n")
# define OPEN_ERR			("ERROR: failed to open file!\n")
# define CO_FAILED			("ERROR: connexion failed!\n")
# define ARG_ERR1			("ERROR: not enough arguments!\n")
# define ARG_ERR2			("ERROR: too many arguments!\n")
# define CMD_NOT_FOUND		("ERROR: command not found: %s\n")
# define FILE_EXIST			("ERROR: file already exists!\n")
# define LOCALHOST_ADDR		("127.0.0.1")

# define CMDS			(6)

typedef struct			s_cmd
{
	int					len;
	char const			*name;
	int					(*interpret)(int *, char *cmd);
}						t_cmd;

void					usage(char *s);

#endif