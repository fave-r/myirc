/*
** my_join.c for my_join in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:30:17 2015 Thibaut Lopez
*/

#include "client.h"

int	my_join_stdin(t_clt *data, char **com)
{
  char	*tmp;

  if (data->s <= 2)
    {
      my_putstr("Not connected to a server\n", 2);
      return (0);
    }
  if (handle_args(com, 2, 3, 1) == 1)
    return (0);
  if (data->channel == NULL || strcmp(com[1], data->channel) != 0)
    {
      tmp = xstrdup(com[1]);
      if (data->channel != NULL)
	free(data->channel);
      data->channel = tmp;
    }
  fill_cb("JOIN ", 5, &data->wcb);
  fill_cb(data->channel, strlen(data->channel), &data->wcb);
  if (com[2] != NULL)
    {
      fill_cb(" ", 1, &data->wcb);
      fill_cb(com[2], strlen(com[2]), &data->wcb);
    }
  fill_cb("\r\n", 2, &data->wcb);
  return (0);
}
