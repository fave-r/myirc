/*
** my_part.c for my_part in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Wed Apr 22 14:41:26 2015 Thibaut Lopez
*/

#include "client.h"

int	my_part_socket(t_clt *data, char **com)
{
  char	*nick;

  (void)data;
  nick = get_nick(com[0]);
  if (com[1] != NULL && com[2] != NULL)
    {
      my_putstr(nick, 1);
      my_putstr(" part from ", 1);
      my_putstr(com[2], 1);
      my_putstr("\n", 1);
    }
  else
    my_putstr("Someone part from this channel\n", 1);
  free(nick);
  return (0);
}
