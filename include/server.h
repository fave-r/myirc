/*
** server.h for irc in /home/fave_r/rendu/PSU_2014_myirc
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Tue Apr  7 10:36:25 2015 romaric
** Last update Wed Apr 22 11:50:30 2015 romaric
*/

#ifndef	 __SRC_SRV__
# define __SRC_SRV__

#include "gnl.h"
#include "parser.h"

t_com	*ptr_to_function();
int	read_com(t_user *data, t_chan *chans);
int	handle_fds(int s, t_user **user);

int	my_accept_file(t_user *data, char **com, t_chan *chans);
int	my_join(t_user *data, char **com, t_chan *chans);
int	my_list(t_user *data, char **com, t_chan *chans);
int	my_message(t_user *data, char **com, t_chan *chans);
int	my_msg(t_user *data, char **com, t_chan *chans);
int	my_nick(t_user *data, char **com, t_chan *chans);
int	my_part(t_user *data, char **com, t_chan *chans);
int	my_send_file(t_user *data, char **com, t_chan *chans);
int	my_users(t_user *data, char **com, t_chan *chans);
int	my_user(t_user *data, char **com, t_chan *chans);
int	my_hello(t_user *data, char **com, t_chan *chans);
int	my_ping(t_user *data, char **com, t_chan *chans);
int	my_pong(t_user *data, char **com, t_chan *chans);
void	clone_us(t_user *user, t_cln **clone);

void	set_fd(int s, t_bf *bf, t_user *user);
void	new_client(int fd, t_user **user, int *nbclient);
void	check_client(t_user **user, t_bf *bf, t_chan *chans);
void	data_free(t_user **data);
int	nbr_on_chan(const t_chan *chan);
void	send_to_chan(t_user *data, char **com, t_chan *chans);
void	send_i_join(t_user *data, const t_chan *chans);
void	not_enough_jmsg(t_user *data, char *com);
void	join_work(t_chan *chan, t_user *data);
t_chan	*put_part_erro(t_user *data, char *com);
int	my_quit(t_user *data, char **com, t_chan *chans);

#endif
