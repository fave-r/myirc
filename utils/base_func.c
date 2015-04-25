/*
** base_func.c for base_func in /home/lopez_t/PSU_2014_myirc
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 17:09:02 2015 Thibaut Lopez
** Last update Wed Apr  8 17:32:49 2015 Thibaut Lopez
*/

#include "my_irc.h"

int	my_putstr(char *str, int fd)
{
  int	rl;
  int	wl;

  rl = strlen(str);
  wl = 0;
  while ((wl = write(fd, str + wl, rl - wl)) != rl);
  return (wl);
}

int	my_strstr(char **tab, char *str)
{
  int	i;

  i = 0;
  while (tab != NULL && tab[i] != NULL)
    {
      if (strcmp(tab[i], str) == 0)
	return (i);
      i++;
    }
  return (-1);
}

char	*my_strcat(char *s1, char *s2)
{
  int	i;
  int	j;
  char	*ret;

  if (s1 == NULL && s2 == NULL)
    return (NULL);
  else if (s1 == NULL && s2 != NULL)
    return (xstrdup(s2));
  else if (s1 != NULL && s2 == NULL)
    return (xstrdup(s1));
  ret = xmalloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
  i = -1;
  while (s1[++i] != 0)
    ret[i] = s1[i];
  j = -1;
  while (s2[++j] != 0)
    ret[i + j] = s2[j];
  ret[i + j] = 0;
  return (ret);
}
