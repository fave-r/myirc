/*
** my_list.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 17:09:25 2015 romaric
** Last update Wed Apr 22 11:19:26 2015 Thibaut Lopez
*/

#include "server.h"

int		nbr_on_chan(const t_chan *chan)
{
  t_cln		*tmp;
  int		i;

  tmp = chan->users;
  i = 0;
  while (tmp != NULL)
    {
      i++;
      tmp = tmp->next;
    }
  return (i);
}

void		print_on(t_chan *tmp, t_user *data, char str[1024])
{
  char		msg[512];

  bzero(msg, 512);
  sprintf(msg, "321 %s Channel :USERS Name\r\n", data->nick);
  fill_cb(msg, strlen(msg), &data->wr);
  bzero(msg, 512);
  sprintf(str, "322 %s %s %d :No messages\r\n",
	  data->nick, tmp->name, nbr_on_chan(tmp));
  fill_cb(str, strlen(str), &data->wr);
  sprintf(msg, "323 %s :End of channel list.\r\n", data->nick);
  fill_cb(msg, strlen(msg), &data->wr);
}

int		list_one_chan(t_chan *chans
			      , t_user *data
      			      , char **com)
{
  char		**c;
  int		i;
  char		str[1024];
  t_chan	*tmp;

  i = -1;
  c = stwt(com[1], ",");
  while (c[++i] != NULL)
    {
      tmp = chans->next;
      while (tmp != chans)
	{
	  if (strcmp(tmp->name, c[i]) == 0)
	    break;
	  tmp = tmp->next;
	}
      bzero(str, 1024);
      if (strcmp(tmp->name, c[i]) == 0)
	print_on(tmp, data, str);
    }
  free(c);
  return (0);
}

void	list_work_msg(t_user *data, t_chan *chans)
{
  char	str[512];

  bzero(str, 512);
  sprintf(str, "321 %s Channel :USERS Name\r\n", data->nick);
  fill_cb(str, strlen(str), &data->wr);
  bzero(str, 512);
  sprintf(str, "322 %s %s %d :No messages\r\n",
	  data->nick, chans->name, nbr_on_chan(chans));
  fill_cb(str, strlen(str), &data->wr);
}

int	my_list(t_user *data, char **com
		, t_chan *chans)
{
  t_chan	*tmp;
  char		str[512];

  bzero(str, 512);
  if (data->usered == 0)
    {
      sprintf(str, "451 LIST not registered\r\n");
      fill_cb(str, strlen(str), &data->wr);
      return (0);
    }
  if (com[1] != NULL)
    return (list_one_chan(chans, data, com));
  list_work_msg(data, chans);
  tmp = chans;
  while ((tmp = tmp->next) != chans)
    {
      bzero(str, 512);
      sprintf(str, "322 %s %s %d :No messages\r\n",
	      data->nick, tmp->name, nbr_on_chan(tmp));
      fill_cb(str, strlen(str), &data->wr);
    }
  bzero(str, 512);
  sprintf(str, "323 %s ::End of channel list.\r\n", data->nick);
  fill_cb(str, strlen(str), &data->wr);
  return (0);
}
