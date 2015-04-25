/*
** my_message.c for my_message in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:29:18 2015 Thibaut Lopez
*/

#include "client.h"

int	my_message(t_clt *data, char *com)
{
  if (data->s <= 2)
    {
      my_putstr("Not connected to a server\n", 2);
      return (0);
    }
  if (data->channel == NULL)
    {
      my_putstr("You must first join a channel\n", 2);
      return (0);
    }
  fill_cb("PRIVMSG ", 8, &data->wcb);
  fill_cb(data->channel, strlen(data->channel), &data->wcb);
  fill_cb(" :", 2, &data->wcb);
  fill_cb(com, strlen(com), &data->wcb);
  fill_cb("\r\n", 2, &data->wcb);
  return (0);
}
