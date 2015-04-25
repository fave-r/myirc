/*
** my_nick.c for my_nick in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 19:39:46 2015 Thibaut Lopez
*/

#include "client.h"

int	my_nick_socket(t_clt *data, char **com)
{
  char	*nick;

  (void)data;
  nick = get_nick(com[0]);
  if (com[1] != NULL && com[2] != NULL)
    printf("%s is now knowed as %s\n", nick, com[2]);
  else
    printf("Someone changed his name\n");
  free(nick);
  return (0);
}
