/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdavid <rdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/17 13:39:27 by rdavid            #+#    #+#             */
/*   Updated: 2015/05/17 20:39:58 by rdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define BIND_ERR			("ERROR: failed to bind!\n")

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
