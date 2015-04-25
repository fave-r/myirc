/*
** my_users.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 17:12:19 2015 romaric
** Last update Sun Apr 12 22:41:53 2015 romaric
*/

#include "server.h"

void		write_my_nick(t_user *data, t_chan *chan)
{
  t_user	*tmp_u;
  char		str[512];
  t_cln		*tmp_c;

  tmp_c = chan->users;
  tmp_u = data;
  while (tmp_c)
    {
      while (tmp_u->prev != NULL)
	tmp_u = tmp_u->prev;
      while (tmp_u->fd != tmp_c->fd)
	tmp_u = tmp_u->next;
      if (tmp_c->fd != data->fd)
	{
	  bzero(str, 512);
	  sprintf(str, "353 %s :%s\r\n", chan->name, tmp_u->nick);
	  fill_cb(str, strlen(str), &data->wr);
	}
      tmp_c = tmp_c->next;
    }
  bzero(str, 512);
  sprintf(str, "366 :End of /NAMES list\r\n");
  fill_cb(str, strlen(str), &data->wr);
}

int             name_one_chan(t_chan *chans
                              , t_user *data
                              , char **com)
{
  char          **c;
  int           i;
  char          str[1024];
  t_chan        *tmp;

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
        write_my_nick(data, tmp);
    }
  free(c);
  return (0);
}

void		name_chan_cur(t_user *data, t_chan *chans)
{
  char		str[512];
  t_chan	*tmp;

  bzero(str, 512);
  if (data->joined == 0)
    {
      sprintf(str, "366 :End of /NAMES list\r\n");
      fill_cb(str, strlen(str), &data->wr);
    }
  else
    {
      tmp = chans->next;
      while (tmp->id != data->chan)
	tmp = tmp->next;
      write_my_nick(data, tmp);
    }
}

int	my_users(t_user *data, char **com
		 , t_chan *chans)
{
  if (com[1] == NULL)
    name_chan_cur(data, chans);
  else
    name_one_chan(chans, data, com);
  return (0);
}
