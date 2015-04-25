/*
** client.h for client in /home/lopez_t/PSU_2014_myirc/src_client
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Tue Apr  7 16:08:19 2015 Thibaut Lopez
** Last update Sun Apr 12 22:06:15 2015 Thibaut Lopez
*/

#ifndef	CLIENT_H
#define	CLIENT_H

#include "gnl.h"

typedef struct	s_clt
{
  int		s;
  char		*ip;
  int		port;
  char		*nick;
  char		*user;
  char		*channel;
  t_cb		sock;
  t_cb		wcb;
  t_cb		stdin;
}		t_clt;

void		init_data(t_clt *, char *, char *);
void		data_free(t_clt *);
void		set_fd(int , t_bf *);
int		read_stdin(t_clt *);
int		read_socket(t_clt *);
int		my_accept_file(t_clt *, char **);
int		my_join_stdin(t_clt *, char **);
int		my_join_socket(t_clt *, char **);
int		my_list(t_clt *, char **);
int		my_message(t_clt *, char *);
int		my_msg(t_clt *, char **);
int		my_nick_stdin(t_clt *, char **);
int		my_nick_socket(t_clt *, char **);
int		my_part_stdin(t_clt *, char **);
int		my_part_socket(t_clt *, char **);
int		my_send_file(t_clt *, char **);
int		my_server(t_clt *, char **);
int		my_users(t_clt *, char **);
int		my_privmsg(t_clt *, char **);
int		my_notice(t_clt *, char **);
int		my_ping(t_clt *, char **);
int		my_error(t_clt *, char **);
int		my_quit(t_clt *, char **);
int		my_quit_stdin(t_clt *, char **);
int		my_code(t_clt *, char **);
char		*get_nick(char *);
int		handle_args(char **, int, int, int);

#endif
