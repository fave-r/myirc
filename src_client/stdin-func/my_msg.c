/*
** my_msg.c for my_msg in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:27:32 2015 Thibaut Lopez
*/

#include "client.h"

int	my_msg(t_clt *data, char **com)
{
  if (data->s <= 2)
    {
      my_putstr("Not connected to a server\n", 2);
      return (0);
    }
  if (handle_args(com, 3, 3, 1) == 1)
    return (0);
  fill_cb("PRIVMSG ", 8, &data->wcb);
  fill_cb(com[1], strlen(com[1]), &data->wcb);
  fill_cb(" ", 1, &data->wcb);
  fill_cb(com[2], strlen(com[2]), &data->wcb);
  fill_cb("\r\n", 2, &data->wcb);
  return (0);
}
