/*
** my_privmsg.c for my_privmsg in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sat Apr 11 17:14:44 2015 Thibaut Lopez
*/

#include "client.h"

int	my_privmsg(t_clt *data, char **com)
{
  int	i;
  char	*mess;
  char	*name;

  (void)data;
  i = 1;
  while (com[i] != NULL && com[i][0] != ':')
    i++;
  if (com[i] == NULL)
    return (0);
  mess = com[i] + 1;
  name = get_nick(com[0]);
  printf("%s vous dit (%s): %s\n", name,
	 (com[2][0] == '#') ? "dans ce channel" : "en privé", mess);
  free(name);
  return (0);
}
