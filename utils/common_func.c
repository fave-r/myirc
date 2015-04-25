/*
** common_func.c for common_func in /home/lopez_t/PSU_2014_myirc
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 17:09:17 2015 Thibaut Lopez
** Last update Thu Apr  9 15:37:26 2015 Thibaut Lopez
*/

#include "my_irc.h"

int		find_ptr(t_com *com, char *str)
{
  int		j;
  size_t	len;

  j = 0;
  while (com[j].com != NULL)
    {
      len = strlen(com[j].com);
      if (len <= strlen(str) && strncmp(str, com[j].com, len) == 0)
	return (j);
      j++;
    }
  return (-1);
}

int	my_strtol(char *nbr)
{
  long	ret;
  char	*err;

  ret = strtol(nbr, &err, 10);
  if (err[0] != 0)
    return (-1);
  if (ret > INT_MAX || ret < 0)
    return (-1);
  return (ret);
}
