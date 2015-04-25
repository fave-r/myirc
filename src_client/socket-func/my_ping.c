/*
** my_ping.c for my_ping in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:27:03 2015 Thibaut Lopez
*/

#include "client.h"

int	my_ping(t_clt *data, char **com)
{
  char	tmp[512];
  int	i;

  i = (com[0][0] == ':') ? 2 : 1;
  if (handle_args(com, i + 1, i + 1, 1) == 1)
    return (0);
  bzero(tmp, 512);
  sprintf(tmp, "PONG %s\r\n", (com[i] == NULL) ? "" : com[i]);
  fill_cb(tmp, strlen(tmp), &data->wcb);
  return (0);
}
