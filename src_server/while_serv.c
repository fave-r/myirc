/*
** while_serv.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Tue Apr  7 10:06:07 2015 romaric
** Last update Wed Apr 22 14:09:01 2015 Thibaut Lopez
*/

#include <signal.h>
#include "server.h"

static int	quit_sig = 0;

void		signal_quit(__attribute__((unused))int signo)
{
  quit_sig = 1;
  write(1, "\n", 1);
}

void		init_handle(int *bool, t_user **user
			    , t_chan **chans,  int *nb)
{
  signal(SIGINT, signal_quit);
  *nb = 1;
  *bool = 0;
  *user = NULL;
  *chans = circular_linked_channel();
}

int			handle_fds(int s, t_user **user)
{
  t_bf			bf;
  int			bool;
  int			nb_client;
  t_chan		*chans;

  init_handle(&bool, user, &chans, &nb_client);
  while (bool != -1)
    {
      if (quit_sig == 1)
      	bool = -1;
      else
      	{
	  set_fd(s, &bf, *user);
	  if ((bool = select(s + nb_client, &bf.rbf, &bf.wbf, NULL, NULL)) != -1)
	    {
	      if (FD_ISSET(s, &bf.rbf))
		new_client(s, user, &nb_client);
	      check_client(user, &bf, chans);
	    }
	}
    }
  return (0);
}

void		data_free(t_user **data)
{
  t_user	*tmp;

  tmp = *data;
  while (tmp != NULL && tmp->next != NULL)
    {
      close(tmp->fd);
      free(tmp->nick);
      free(tmp->username);
      free(tmp->realname);
      free_cb(&tmp->cb);
      free_cb(&tmp->wr);
      tmp = tmp->next;
      free(tmp->prev);
    }
  if (tmp != NULL)
    free(tmp);
}

