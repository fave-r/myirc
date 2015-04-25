/*
** my_join.c for my_join in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 19:38:52 2015 Thibaut Lopez
*/

#include "client.h"

int	my_join_socket(t_clt *data, char **com)
{
  char	*nick;

  (void)data;
  nick = get_nick(com[0]);
  printf("%s joins %s\n", nick,
	 (com[1] == NULL || com[2] == NULL) ? "" : com[2]);
  free(nick);
  return (0);
}
