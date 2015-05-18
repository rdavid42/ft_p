/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 13:39:27 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/18 10:15:29 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define BIND_ERR			("ERROR: failed to bind!\n")
# define ROOT_DIR_DENIED	("ERROR: root directory denied!\n")
# define CWD_DENIED			("ERROR: current directory denied!")

int							create_server(int port);
void						usage(char *s);
int							ls(int *cs, char *cmd);
int							get(int *cs, char *cmd);
int							cd(char *root, int *cs, char *cmd);
int							create_server(int port);
int							handle_client(char *root, int cs);
int							server_loop(int sock);
int							interpret_command(char *root, int *cs, char *cmd);

#endif
