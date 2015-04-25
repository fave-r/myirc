/*
** my_part.c for my_part in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:29:01 2015 Thibaut Lopez
*/

#include "client.h"

int	my_part_stdin(t_clt *data, char **com)
{
  if (data->s <= 2)
    {
      my_putstr("Not connected to a server\n", 2);
      return (0);
    }
  if (handle_args(com, 2, 2, 1) == 1)
    return (0);
  if (data->channel == NULL || strcmp(com[1], data->channel) != 0)
    {
      my_putstr("You're not part of this channel\n", 2);
      return (0);
    }
  free(data->channel);
  data->channel = NULL;
  fill_cb("PART ", 5, &data->wcb);
  fill_cb(com[1], strlen(com[1]), &data->wcb);
  fill_cb("\r\n", 2, &data->wcb);
  return (0);
}
