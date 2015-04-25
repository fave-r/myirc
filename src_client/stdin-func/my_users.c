/*
** my_users.c for my_users in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:29:53 2015 Thibaut Lopez
*/

#include "client.h"

int	my_users(t_clt *data, char **com)
{
  if (data->s <= 2)
    {
      my_putstr("Not connected to a server\n", 2);
      return (0);
    }
  if (handle_args(com, 1, 1, 1) == 1)
    return (0);
  fill_cb("NAMES\r\n", 7, &data->wcb);
  return (0);
}
