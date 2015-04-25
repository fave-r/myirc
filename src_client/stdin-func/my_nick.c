/*
** my_nick.c for my_nick in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:29:41 2015 Thibaut Lopez
*/

#include "client.h"

int	my_nick_stdin(t_clt *data, char **com)
{
  char	*tmp;

  if (data->s <= 2)
    {
      my_putstr("Not connected to a server\n", 2);
      return (0);
    }
  if (handle_args(com, 2, 2, 1) == 1)
    return (0);
  if (strcmp(com[1], data->nick) != 0)
    {
      tmp = xstrdup(com[1]);
      free(data->nick);
      data->nick = tmp;
    }
  fill_cb("NICK ", 5, &data->wcb);
  fill_cb(data->nick, strlen(data->nick), &data->wcb);
  fill_cb("\r\n", 2, &data->wcb);
  return (0);
}
