/*
** str_func.c for str_func in /home/lopez_t/PSU_2014_myftp/src/src-serveur/Parser
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Sun Mar 22 15:56:55 2015 Thibaut Lopez
** Last update Wed Apr  8 17:56:06 2015 Thibaut Lopez
*/

#include "parser.h"

char		**sfree(char **str)
{
  int		i;

  if (str == NULL)
    return (NULL);
  i = 0;
  while (str[i] != NULL)
    {
      free(str[i]);
      i++;
    }
  free(str);
  return (NULL);
}

int		sstrlen(char **str)
{
  int		i;

  if (str == NULL)
    return (0);
  i = 0;
  while (str[i] != NULL)
    i++;
  return (i);
}

char		**sstrcat(char **str, char *ad)
{
  int		i;
  char		**ret;

  i = 0;
  ret = xmalloc((sstrlen(str) + 2) * sizeof(char *));
  while (str != NULL && str[i] != NULL)
    {
      ret[i] = xstrdup(str[i]);
      i++;
    }
  ret[i] = ad;
  ret[i + 1] = NULL;
  sfree(str);
  return (ret);
}
