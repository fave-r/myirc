/*
** my_msg.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 17:09:53 2015 romaric
** Last update Thu Apr 23 10:35:25 2015 romaric
*/

#include "server.h"

void		send_chan_msg(t_user *user, char **com, t_user *data, int i)
{
  char		str[4096];
  char		err[512];

  if (i == 2)
    {
      bzero(str, 4096);
      sprintf(str, ":%s!%s@%s.IP PRIVMSG %s %s\r\n", data->nick
	      , data->username, data->ip, com[1], com[2]);
      fill_cb(str, strlen(str), &user->wr);
    }
  else
    {
      bzero(err, 512);
      sprintf(err, "404 %s :Cannot send to channel\r\n", com[1]);
      fill_cb(err, strlen(err), &data->wr);
    }
}

void		send_to_chan(t_user *data, char **com, t_chan *chans)
{
  t_chan	*tmp;
  t_cln		*tmp_c;
  t_user	*tmp_u;

  tmp_u = NULL;
  tmp = chans->next;
  while (tmp != chans && tmp->id != data->chan)
    tmp = tmp->next;
  if (strcmp(tmp->name, com[1]) != 0)
    {
      send_chan_msg(tmp_u, com, data, 1);
      return;
    }
  tmp_c = tmp->users;
  tmp_u = data;
  while (tmp_c)
    {
      while (tmp_u->prev != NULL)
	tmp_u = tmp_u->prev;
      while (tmp_u->fd != tmp_c->fd)
	tmp_u = tmp_u->next;
      if (tmp_c->fd != data->fd)
	send_chan_msg(tmp_u, com, data, 2);
      tmp_c = tmp_c->next;
    }
}

void		send_priv_msg(t_user *receiv, char **com, t_user *data)
{
  char		str[4096];

  bzero(str, 4096);
  sprintf(str, ":%s!%s@%s.IP PRIVMSG %s %s\r\n", data->nick
	  , data->username, data->ip, com[1], com[2]);
  fill_cb(str, strlen(str), &receiv->wr);
}

void		send_priv(t_user *data, char **com)
{
  t_user	*tmp;
  t_user	*save;
  char		str[512];

  tmp = data;
  save = NULL;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp != NULL)
    {
      if (strcmp(com[1], tmp->nick) == 0)
	save = tmp;
      tmp = tmp->next;
    }
  if (save == NULL)
    {
      bzero(str, 512);
      sprintf(str, "401 %s :No such nick\r\n", com[1]);
      fill_cb(str, strlen(str), &data->wr);
      return;
    }
  send_priv_msg(save, com, data);
}

int	my_msg(t_user *data, char **com
	       , t_chan *chans)
{
  if (com[1] == NULL)
    fill_cb("411 :No recipient given (PRIVMSG)\r\n", 35, &data->wr);
  else if (com[2] == NULL || com[2][0] != ':')
    fill_cb("412 :No text to send\r\n", 22, &data->wr);
  else if (com[1][0] == '#')
    {
      if (data->chan == -1)
	fill_cb("404 #this :Cannot send to channel\r\n", 35, &data->wr);
      else
	send_to_chan(data, com, chans);
    }
  else
    send_priv(data, com);
  return (0);
}
