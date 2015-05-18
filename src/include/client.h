/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 17:50:18 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 17:02:29 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define REQ_ERR			("ERROR: failed to send request!\n")
# define REC_ERR			("ERROR: failed to receive data!\n")
# define CO_CLOSED			("ERROR: connexion closed!\n")
# define CO_FAILED			("ERROR: connexion failed!\n")
# define ARG_ERR1			("ERROR: not enough arguments!\n")
# define ARG_ERR2			("ERROR: too many arguments!\n")
# define CMD_NOT_FOUND		("ERROR: command not found: %s\n")
# define FILE_NOT_FOUND		("ERROR: file not found!\n")
# define PERM_DENIED		("ERROR: permission denied!\n")
# define NO_SUCH_DIR		("ERROR: no such directory!\n")
# define LOCALHOST_ADDR		("127.0.0.1")

# define CMDS				(6)

typedef struct				s_cmd
{
	int						len;
	char const				*name;
	int						(*interpret)(int *, char *cmd);
}							t_cmd;

void						usage(char *s);
int							ls(int *sock, char *cmd);
int							get(int *sock, char *cmd);
int							cd(int *sock, char *cmd);
int							put(int *sock, char *cmd);
int							pwd(int *sock, char *cmd);
int							quit(int *sock, char *cmd);
int							create_client(char *addr, int port);
int							client_loop(int sock);
void						interpret_command(int sock, char *cmd);

#endif
