/*
** fd_func.c for fd_func in /home/lopez_t/PSU_2014_myftp/src/src-serveur
**
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
**
** Started on  Sat Mar 21 20:04:42 2015 Thibaut Lopez
** Last update Wed Apr 22 14:02:20 2015 Thibaut Lopez
*/

#include "server.h"

void	set_fd(int s, t_bf *bf, t_user *user)
{
  t_user	*tmp;

  FD_ZERO(&(bf->rbf));
  FD_ZERO(&(bf->wbf));
  FD_SET(s, &(bf->rbf));
  if (user != NULL)
    {
      tmp = user;
      while (tmp != NULL)
	{
	  FD_SET(tmp->fd, &(bf->rbf));
	  if (cb_taken(&tmp->wr) > 0)
	    FD_SET(tmp->fd, &(bf->wbf));
	  tmp = tmp->next;
	}
    }
}

void			push_back(t_user **user, t_user *to_add)
{
  t_user	*tmp;

  tmp = *user;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = to_add;
  to_add->prev = tmp;
}

void			new_client(int fd, t_user **user, int *nbclient)
{
  t_user		*new;
  struct sockaddr_in	sin;
  socklen_t		len;

  *nbclient = *nbclient + 1;
  new = xmalloc(sizeof(t_user));
  len = sizeof(sin);
  new->fd = accept(fd, (struct sockaddr *)&sin, &len);
  new->ip = inet_ntoa(sin.sin_addr);
  new->nick = xstrdup("Anonymous");
  new->next = NULL;
  new->prev = NULL;
  new->usered = 0;
  new->nicked = 0;
  new->joined = 0;
  new->tokill = 0;
  new->chan = -1;
  new->username = xstrdup("Anonymous");
  new->realname = xstrdup("Anonymous");
  init_cb(&new->cb, 4096, sizeof(char));
  init_cb(&new->wr, 4096, sizeof(char));
  if (*user != NULL)
    push_back(user, new);
  else
    *user = new;
}
