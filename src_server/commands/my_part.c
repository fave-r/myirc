/*
** my_part.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 17:10:17 2015 romaric
** Last update Wed Apr 22 16:10:15 2015 Thibaut Lopez
*/

#include "server.h"

void		send_me_voy_msg(t_user *user, char **com, t_user *data)
{
  char		str[4096];

  bzero(str, 4096);
  sprintf(str, ":%s!%s@%s.IP PART %s\r\n", data->nick
	  , data->username, data->ip, com[1]);
  fill_cb(str, strlen(str), &user->wr);
}

void		send_me_voy(t_user *data, char **com, const t_chan *chans)
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
      send_me_voy_msg(tmp_u, com, data);
      tmp_c = tmp_c->next;
    }
}

t_chan		*check_part(t_chan *chans
			    , t_user *data
			    , char **com, t_chan *tmp)
{
  char		str[512];

  if (com[1] != NULL)
    {
      while (tmp != chans)
	{
	  if (strcmp(tmp->name, com[1]) == 0)
	    break;
	  tmp = tmp->next;
	}
      if (strcmp(tmp->name, com[1]) != 0)
	return (put_part_erro(data, com[1]));
      if (tmp->id != data->chan)
	return (put_part_erro(data, com[1]));
      return (tmp);
    }
  else
    {
      bzero(str, 512);
      sprintf(str, "461 PART :Not enough parameters\r\n");
      fill_cb(str, strlen(str), &data->wr);
    }
  return (NULL);
}

void		part_msg(t_user *data, t_chan *tmp
			 , __attribute__((unused))t_chan *chans)
{
  char		**com;
  char		str[500];

  bzero(str, 500);
  com = xmalloc(4 * sizeof(char *));
  com[0] = xstrdup("PART");
  com[1] = xstrdup(tmp->name);
  com[2] = NULL;
  send_me_voy(data, com, tmp);
  free(com[0]);
  free(com[1]);
  free(com);
}

int		my_part(t_user *data, char **com
			, t_chan *chans)
{
  t_chan	*tmp;
  t_cln		*c;

  tmp = chans->next;
  if ((tmp = check_part(chans, data, com, tmp)) == NULL)
    return (0);
  part_msg(data, tmp, chans);
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
  data->joined = 0;
  data->chan = -1;
  return (0);
}
