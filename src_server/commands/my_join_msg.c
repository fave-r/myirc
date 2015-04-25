/*
** my_join_msg.c for inrealcontext in /home/fave_r/rendu/PSU_2014_myirc
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Sun Apr 12 19:16:44 2015 romaric
** Last update Wed Apr 22 16:09:14 2015 Thibaut Lopez
*/

#include "server.h"

void		send_the_join(t_user *user, char *com, t_user *data)
{
  char		str[4096];

  bzero(str, 4096);
  sprintf(str, ":%s!%s@%s.IP JOIN %s\r\n", data->nick
          , data->username, data->ip, com);
  fill_cb(str, strlen(str), &user->wr);
}

void		send_i_join(t_user *data, const t_chan *chans)
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
      send_the_join(tmp_u, chans->name, data);
      tmp_c = tmp_c->next;
    }
}

void		not_enough_jmsg(t_user *data, char *com)
{
  char		err[512];

  bzero(err, 512);
  sprintf(err, "403 %s %s :No such channel\r\n", data->nick, com);
  fill_cb(err, strlen(err), &data->wr);
}

void		join_work(t_chan *chan, t_user *data)
{
  char		str[512];

  bzero(str, 512);
  sprintf(str, "332 %s %s\r\n", data->nick, chan->name);
  fill_cb(str, strlen(str), &data->wr);
  bzero(str, 512);
  sprintf(str, "333 %s %s\r\n", data->nick, chan->name);
  fill_cb(str, strlen(str), &data->wr);
}
