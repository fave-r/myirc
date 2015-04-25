/*
** stwt.c for stwt in /home/lopez_t/PSU_2014_myirc/utils
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 19:26:53 2015 Thibaut Lopez
** Last update Fri Apr 10 19:07:45 2015 Thibaut Lopez
*/

#include "my_irc.h"

char	*skip_delim(char *str, char *delim)
{
  while (str[0] != 0 && strchr(delim, str[0]) != NULL)
    str++;
  return (str);
}

int	skip_word(char *str, char *delim, int nb_word)
{
  int	i;

  i = 0;
  if (nb_word > 1 && str[0] == ':')
    while (str[i] != 0)
      i++;
  else
    while (str[i] != 0 && strchr(delim, str[i]) == NULL)
      i++;
  return (i);
}

int	lenword(char *str, int *nb_letters, char *delim)
{
  int	len;

  len = 0;
  while (str != NULL && (str = skip_delim(str, delim))[0] != 0)
    {
      len++;
      *nb_letters += (skip_word(str, delim, len) + 1) * sizeof(char);
      str += skip_word(str, delim, len);
    }
  return (len);
}

char	**stwt(char *str, char *delim)
{
  int	i;
  int	nb_word;
  int	nb_letters;
  char	**ret;
  char	*cur;

  nb_letters = 0;
  if ((nb_word = lenword(str, &nb_letters, delim)) == 0)
    return (NULL);
  ret = xmalloc((nb_word + 1) * sizeof(char *) + nb_letters);
  nb_letters = 0;
  cur = (char *)ret + (nb_word + 1) * sizeof(char *);
  i = -1;
  while (nb_word > ++i)
    {
      str = skip_delim(str, delim);
      nb_letters = skip_word(str, delim, i);
      strncpy(cur, str, nb_letters);
      cur[nb_letters] = 0;
      ret[i] = cur;
      str += nb_letters;
      cur += nb_letters + 1;
    }
  ret[i] = NULL;
  return (ret);
}
