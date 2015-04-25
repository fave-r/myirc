/*
** get_next_line.c for get_next_line in /home/lopez_t/PSU_2014_myirc
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 17:09:36 2015 Thibaut Lopez
** Last update Wed Apr  8 17:34:55 2015 Thibaut Lopez
*/

#include "my_irc.h"

char		my_getchar(int fd)
{
  static char	buffer[BUFF_SIZE + 1];
  static int	i = 0;
  static int	test;
  char		c;

  if (buffer[i] == 0)
    i = 0;
  if (i == 0)
    {
      if ((test = read(fd, buffer, BUFF_SIZE)) == -1)
	return (-1);
      buffer[test] = '\0';
    }
  if (test == 0 && buffer[i] == '\0')
    return (0);
  else if (buffer[i] == '\0')
    {
      i = 0;
      return (0);
    }
  c = buffer[i];
  i++;
  return (c);
}

char		*get_next_line(const int fd)
{
  char		*str;
  char		c;
  int		i;

  i = 0;
  str = xmalloc(BUFF_SIZE * sizeof(char));
  while ((c = my_getchar(fd)) != '\n')
    {
      str[i] = c;
      if (c == -1 || (i == 0 && str[i] == '\0'))
	{
	  free(str);
	  return (NULL);
	}
      if (str[i] == '\0')
	return (str);
      i++;
      if (i > 0 && ((i % BUFF_SIZE) == 0))
	if ((str = realloc(str, (i + BUFF_SIZE))) == NULL)
	  return (NULL);
    }
  str[i] = '\0';
  return (str);
}
