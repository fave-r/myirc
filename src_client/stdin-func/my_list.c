/*
** my_list.c for my_list in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:31:04 2015 Thibaut Lopez
*/

#include "client.h"

int	my_list(t_clt *data, char **com)
{
  int	i;

  if (data->s <= 2)
    {
      my_putstr("Not connected to a server\n", 2);
      return (0);
    }
  fill_cb("LIST", 4, &data->wcb);
  i = 1;
  while (com[i] != NULL)
    {
      fill_cb((i == 0) ? " " : ",", 1, &data->wcb);
      fill_cb(com[i], strlen(com[i]), &data->wcb);
      i++;
    }
  fill_cb("\r\n", 2, &data->wcb);
  return (0);
}
