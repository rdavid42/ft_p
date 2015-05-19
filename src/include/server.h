/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 13:39:27 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/19 16:29:59 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define CMDS				(6)

# define BIND_ERR			("ERROR: failed to bind!\n")
# define ROOT_DIR_DENIED	("ERROR: root directory denied!\n")
# define CWD_DENIED			("ERROR: current directory denied!")

typedef struct				s_cmd
{
	int						len;
	char const				*name;
	int						(*interpret)(char *, int *, char *, int *);
}							t_cmd;

int							g_except;

int							create_server(int port);
void						usage(char *s);
int							ls(char *root, int *cs, char *cmd, int *id);
int							get(char *root, int *cs, char *cmd, int *id);
int							cd(char *root, int *cs, char *cmd, int *id);
int							put(char *root, int *cs, char *cmd, int *id);
int							pwd(char *root, int *cs, char *cmd, int *id);
int							quit(char *root, int *cs, char *cmd, int *id);
int							create_server(int port);
int							handle_client(char *root, int cs, int id);
int							server_loop(int sock);
int							interpret_command(char *root, int *cs,
											char *cmd, int *id);

#endif
