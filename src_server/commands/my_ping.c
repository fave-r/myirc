/*
** my_ping.c for irc in /home/fave_r/rendu/PSU_2014_myirc/src_server/commands
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 17:08:47 2015 romaric
** Last update Tue Apr 21 18:33:29 2015 Thibaut Lopez
*/

#include "server.h"

int		my_ping(t_user *data, char **com
			, __attribute__((unused))t_chan *chans)
{
  char		ret[512];

  bzero(ret, 512);
  if (com[1] != NULL && com[2] != NULL)
    {
      sprintf(ret, "461 %s PING :Too many parameters\r\n", data->nick);
      fill_cb(ret, strlen(ret), &data->wr);
      return (0);
    }
  sprintf(ret, "PONG %s\r\n", (com[1] == NULL) ? "" : com[1]);
  fill_cb(ret, strlen(ret), &data->wr);
  return (0);
}
