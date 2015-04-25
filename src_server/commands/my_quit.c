/*
** my_quit.c for irc in /home/fave_r/rendu/PSU_2014_myirc
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Wed Apr 22 11:41:01 2015 romaric
** Last update Wed Apr 22 16:10:30 2015 Thibaut Lopez
*/

#include "server.h"

t_chan		*check_chan_is(t_user *data
			       , t_chan *chans)
{
  t_chan	*tmp;

  tmp = chans->next;
  while (tmp != chans)
    {
      if (tmp->id == data->chan)
	break;
      tmp = tmp->next;
    }
  if (tmp->id == data->chan)
    return (tmp);
  return (NULL);
}

void		send_me_voyq_msg(t_user *user, char **com, t_user *data)
{
  char		str[4096];

  bzero(str, 4096);
  sprintf(str, ":%s!%s@%s.IP QUIT :Self-Quit: %s\r\n", data->nick
          , data->username, data->ip
	  , com[1] == NULL ? ":leaving" : com[1]);
  fill_cb(str, strlen(str), &user->wr);
}

void		go_out(t_user *data, t_chan *tmp)
{
  t_cln		*c;

  if (nbr_on_chan(tmp) == 1)
    tmp->users = NULL;
  else
    {
      c = tmp->users;
      while (c->fd != data->fd)
        c = c->next;
      if (c->next == NULL)
        c->prev->next = NULL;
      else if (c->prev == NULL)
        tmp->users = c->next;
      else
        c->prev->next = c->next;
      free(c);
    }
}

void		msg_quit(t_user *data, char **com
			 , t_chan *chans)
{
  t_cln		*tmp_c;
  t_user	*tmp_u;

  if (check_chan_is(data, chans) != NULL)
    {
      go_out(data, check_chan_is(data, chans));
      tmp_c = check_chan_is(data, chans)->users;
      tmp_u = data;
      while (tmp_c)
	{
	  while (tmp_u->prev != NULL)
	    tmp_u = tmp_u->prev;
	  while (tmp_u->fd != tmp_c->fd)
	    tmp_u = tmp_u->next;
	  send_me_voyq_msg(tmp_u, com, data);
	  tmp_c = tmp_c->next;
	}
    }
}

int	my_quit(t_user *data, char **com
		, t_chan *chans)
{
  if (data->chan != -1 && data->joined != 0)
    msg_quit(data, com, chans);
  data->tokill = 1;
  return (0);
}
