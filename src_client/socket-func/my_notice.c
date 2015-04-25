/*
** my_notice.c for my_notice in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sat Apr 11 00:49:25 2015 Thibaut Lopez
*/

#include "client.h"

int	my_notice(t_clt *data, char **com)
{
  int	i;

  (void)data;
  i = (com[0][0] == ':') ? 3 : 2;
  if (handle_args(com, i + 1, i + 1, 1) == 1)
    return (0);
  printf("%s: %s\n", com[i - 1], (com[i][0] == ':') ? com[i] + 1 : com[i]);
  return (0);
}
