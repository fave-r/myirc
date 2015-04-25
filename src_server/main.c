/*
** main.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Tue Apr  7 10:03:44 2015 romaric
** Last update Wed Apr 22 14:30:19 2015 Thibaut Lopez
*/

#include "server.h"

void		unit_user_free(t_user *user)
{
  close(user->fd);
  free(user->nick);
  free(user->username);
  free(user->realname);
  free_cb(&user->cb);
  free_cb(&user->wr);
  if (user->prev != NULL)
    user->prev->next = user->next;
  if (user->next != NULL)
    user->next->prev = user->prev;
  free(user);
}

void		check_client(t_user **user, t_bf *bf, t_chan *chans)
{
  t_user	*tmp;

  tmp = *user;
  while (tmp != NULL)
    {
      if (cb_taken(&tmp->wr) > 0 && FD_ISSET(tmp->fd, &bf->wbf))
	write_cb(&tmp->wr, tmp->fd);
      if (FD_ISSET(tmp->fd, &bf->rbf))
	read_com(tmp, chans);
      if (tmp->tokill == 1)
	{
	  *user = (tmp == *user) ? (*user)->next : *user;
	  if (tmp->next == NULL)
	    {
	      unit_user_free(tmp);
	      tmp = NULL;
	    }
	  else
	    unit_user_free((tmp = tmp->next)->prev);
	}
      else
	tmp = tmp->next;
    }
}

int			main(int ac, char **av)
{
  int			s;
  int			port;
  t_user		*user;

  if (ac != 2)
    port = 6667;
  else
    port = atoi(av[1]);
  if ((s = init_socket()) == -1)
    return (1);
  if (init_bind(s, &port) == -1)
    return (clean_return(s, "Couldn't bind"));
  if (listen(s, 42) == -1)
    return (clean_return(s, "Couldn't listen"));
  handle_fds(s, &user);
  data_free(&user);
  close(s);
  return (0);
}
