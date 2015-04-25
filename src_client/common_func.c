/*
** common_func.c for common_func.c in /home/lopez_t/PSU_2014_myirc/src_client/stdin-func
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Thu Apr  9 09:22:53 2015 Thibaut Lopez
** Last update Sat Apr 11 17:18:28 2015 Thibaut Lopez
*/

#include "client.h"

char	*get_nick(char *str)
{
  int	len;
  char	*ret;

  len = 1;
  while (str[len] != 0 && str[len] != '!' && str[len] != '@')
    len++;
  ret = strndup(str + 1, len - 1);
  if (ret == NULL)
    exit(1);
  return (ret);
}

int	handle_args(char **args, int min, int max, int verbose)
{
  int	len;

  len = sstrlen(args);
  if (len < min)
    {
      if (verbose == 1)
	fprintf(stderr, "Too few argument in function '%s'\n", args[0]);
      return (1);
    }
  else if (len > max)
    {
      if (verbose == 1)
	fprintf(stderr, "Too many argument in function '%s'\n", args[0]);
      return (1);
    }
  return (0);
}
