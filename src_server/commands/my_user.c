/*
** my_user.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Fri Apr 10 12:17:51 2015 romaric
** Last update Thu Apr 23 10:35:45 2015 romaric
*/

#include "server.h"

void	my_user_msg_err(t_user *data)
{
  char	str[512];

  bzero(str, 512);
  sprintf(str, "462 :You may not reregister\r\n");
  fill_cb(str, strlen(str), &data->wr);
}

int		nbr_user(t_user *data)
{
  t_user	*tmp;
  int		ret;

  ret = 1;
  tmp = data;
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  while (tmp->next != NULL)
    {
      ret++;
      tmp = tmp->next;
    }
  return (ret);
}

int		nbr_chan(t_chan *data)
{
  t_chan	*tmp;
  int		ret;

  ret = 1;
  tmp = data;
  while (tmp->next != data)
    {
      ret++;
      tmp = tmp->next;
    }
  return (ret);
}

void	successful_login(t_user *data, t_chan *chans)
{
  int	users;
  char	str[512];

  data->usered = 1;
  users = nbr_user(data);
  bzero(str, 512);
  fill_cb("PING IRCServer\r\n", 16, &data->wr);
  sprintf(str, "375 %s :- irc.bulls.org Message of the Day -\r\n\
376 %s :End of message of the day.\r\n", data->nick, data->nick);
  fill_cb(str, strlen(str), &data->wr);
  bzero(str, 512);
  sprintf(str, "251 %s :There are %d users and 0 invisible on 1 servers\r\n\
252 %s 0 :operator(s) online\r\n", data->nick, users, data->nick);
  fill_cb(str, strlen(str), &data->wr);
  bzero(str, 512);
  sprintf(str, "254 %s %d :channels formed\r\n\
255 %s :I have %d clients and 1 servers\r\n",
	  data->nick, nbr_chan(chans), data->nick, nbr_user(data));
  fill_cb(str, strlen(str), &data->wr);
  bzero(str, 512);
  sprintf(str, "265 %s :Current Local Users: %d  Max: 100\r\n\
266 %s :Current Global Users: %d  Max: 100\r\n",
	  data->nick, users, data->nick, users);
  fill_cb(str, strlen(str), &data->wr);
}

int	my_user(t_user *data, char **com, t_chan *chans)
{
  char	err[500];
  char	str[512];
  int	i;

  bzero(err, 500);
  bzero(str, 512);
  i = -1;
  if (sstrlen(com) < 5)
    {
      while (com[++i] != NULL)
	sprintf(err, "%s %s", err, com[i]);
      sprintf(str, "461 %s :Not enough parameters\r\n", err);
      fill_cb(str, strlen(str), &data->wr);
    }
  else if (data->usered == 1)
    my_user_msg_err(data);
  else
    {
      free(data->username);
      free(data->realname);
      data->username = xstrdup(com[1]);
      data->realname = xstrdup(com[4]);
      successful_login(data, chans);
    }
  return (0);
}
