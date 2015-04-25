/*
** my_nick.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 17:05:27 2015 romaric
** Last update Wed Apr 22 16:17:59 2015 Thibaut Lopez
*/

#include "server.h"

void		send_the_nick(t_user *user, char *com, t_user *data)
{
  char		str[4096];

  bzero(str, 4096);
  sprintf(str, ":%s!%s@%s.IP NICK %s\r\n", data->nick
          , data->username, data->ip, com);
  fill_cb(str, strlen(str), &user->wr);
}

void		send_new_nick(t_user *data, const t_chan *chans, char *nnick)
{
  t_cln		*tmp_c;
  t_user	*tmp_u;

  tmp_c = chans->users;
  tmp_u = data;
  while (tmp_c)
    {
      while (tmp_u->prev != NULL)
        tmp_u = tmp_u->prev;
      while (tmp_u->fd != tmp_c->fd)
        tmp_u = tmp_u->next;
      send_the_nick(tmp_u, nnick, data);
      tmp_c = tmp_c->next;
    }
}

void		check_chan(t_user *data, t_chan *chans, char *nnick)
{
  t_chan	*tmp;

  if (data->joined == 1)
    {
      tmp = chans->next;
      while (tmp->id != data->chan)
	tmp = tmp->next;
      send_new_nick(data, chans, nnick);
    }
  else
    send_the_nick(data, nnick, data);
}

int		check_nick(t_user *data, char *nick)
{
  t_user	*tmp;
  int		ok;
  char		err[512];

  ok = 0;
  tmp = data;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp != NULL)
    {
      if (strcmp(nick, tmp->nick) == 0)
	{
	  ok = -1;
	  break;
	}
      tmp = tmp->next;
    }
  bzero(err, 512);
  if (ok == -1)
    {
      sprintf(err, "433 %s :Nickname is already in use\r\n", nick);
      fill_cb(err, strlen(err), &data->wr);
    }
  return (ok);
}

int	my_nick(t_user *data, char **com
		, __attribute__((unused))t_chan *chans)
{
  char		err[512];

  if (com[1] != NULL)
    {
      if (check_nick(data, com[1]) != -1)
	{
	  check_chan(data, chans, com[1]);
	  free(data->nick);
	  data->nick = xstrdup(com[1]);
	  data->nicked = 1;
	}
    }
  else
    {
      bzero(err, 512);
      sprintf(err, "461 %s NICK :Not enough parameters.\r\n", data->nick);
      fill_cb(err, strlen(err), &data->wr);
      bzero(err, 512);
      sprintf(err, "304 %s :SYNTAX NICK <newnick>\r\n", data->nick);
      fill_cb(err, strlen(err), &data->wr);
    }
  return (0);
}
