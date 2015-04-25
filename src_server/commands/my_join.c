/*
** my_join.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 17:11:05 2015 romaric
** Last update Wed Apr 22 16:27:03 2015 Thibaut Lopez
*/

#include "server.h"

int		verify_key(t_chan *chan, t_user *data, char **com)
{
  int		ret;
  char		err[512];

  ret = -1;
  bzero(err, 512);
  if (chan->pass[0] == '\0')
    return (0);
  if (com[2] == NULL)
    {
      sprintf(err
	      , "403 %s %s :Not enough parameters\r\n"
	      , com[0], com[1]);
      fill_cb(err, strlen(err), &data->wr);
    }
  else if (strcmp(chan->pass, com[2]) != 0)
    {
      sprintf(err
	      , "403 %s :Cannot join channel (+k)\r\n"
	      , chan->name);
      fill_cb(err, strlen(err), &data->wr);
    }
  else
    ret = 0;
  return (ret);
}

void		join_this_serv(t_chan *chan, t_user *data, char **com)
{
  t_cln		*tmp;
  t_cln		*_tmp;

  clone_us(data, &tmp);
  if (verify_key(chan, data, com) == 0)
    {
      send_i_join(data, chan);
      if (chan->users == NULL)
	chan->users = tmp;
      else
	{
	  _tmp = chan->users;
	  while (_tmp->next != NULL)
	    _tmp = _tmp->next;
	  _tmp->next = tmp;
	  tmp->prev = _tmp;
	}
      data->chan = chan->id;
      join_work(chan, data);
      data->joined = 1;
    }
}

int		invalid_user_arg(t_user *data
				 , const char *nick
				 , const char *com, const int err)
{
  char		str[512];

  bzero(str, 512);
  if (data->joined == 1)
    {
      sprintf(str, "451 JOIN already\r\n");
      fill_cb(str, strlen(str), &data->wr);
      return (0);
    }
  if (err == 1)
    {
      sprintf(str, "403 %s %s :Invalid channel name\r\n", nick, com);
      fill_cb(str, strlen(str), &data->wr);
    }
  else
    {
      sprintf(str, "451 JOIN not registered\r\n");
      fill_cb(str, strlen(str), &data->wr);
    }
  return (0);
}

void		not_enough_param(const char *nick, t_user *data)
{
  char		err[512];

  bzero(err, 512);
  sprintf(err, "461 %s JOIN :Not enough parameters\r\n", nick);
  fill_cb(err, strlen(err), &data->wr);
  bzero(err, 512);
  sprintf(err
	  , "304 %s :SYNTAX JOIN <channel>{,<channel>} {<key>{,<key>}}\r\n"
	  , nick);
  fill_cb(err, strlen(err), &data->wr);
}

int		my_join(t_user *data, char **com, t_chan *chans)
{
  t_chan	*tmp;

  if (com[1] != NULL)
    {
      if (data->usered == 0 || data->joined == 1)
	return (invalid_user_arg(data, data->nick, com[1], 2));
      if (com[1][0] != '#')
	return (invalid_user_arg(data, data->nick, com[1], 1));
      tmp = chans->next;
      while (tmp != chans)
	{
	  if (strcmp(tmp->name, com[1]) == 0)
	    break;
	  tmp = tmp->next;
	}
      if (strcmp(tmp->name, com[1]) == 0)
	join_this_serv(tmp, data, com);
      else if (strcmp(chans->name, com[1]) == 0)
	join_this_serv(chans, data, com);
      else
	not_enough_jmsg(data, com[1]);
    }
  else
    not_enough_param(data->nick, data);
  return (0);
}
