/*
** read_cb.c for read_cb in /home/lopez_t/PSU_2014_myirc/utils/CircularBuffer
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Fri Apr 10 10:17:56 2015 Thibaut Lopez
** Last update Sun Apr 12 19:05:50 2015 Thibaut Lopez
*/

#include "my_irc.h"

void	*flush_cb(t_cb *cb)
{
  bzero(cb->buff, cb->cap * cb->sz);
  cb->beg = 0;
  cb->end = 0;
  return (NULL);
}

char	*get_line_cb(t_cb *cb)
{
  int	ret;
  char	*str;

  str = NULL;
  if ((ret = cbchr(cb, "\r")) != -1 || (ret = cbchr(cb, "\n")) != -1)
    {
      str = get_cb(ret + 1, cb);
      str[ret] = 0;
    }
  return (str);
}

char	*read_cb(t_cb *cb, int fd)
{
  int	rl;
  char	*str;

  str = xmalloc(500 * sizeof(char));
  rl = read(fd, str, 499);
  str[rl] = 0;
  if (str != NULL && rl > 0)
    if (fill_cb(str, rl, cb) == 1)
      return (flush_cb(cb));
  if (str != NULL)
    free(str);
  return (get_line_cb(cb));
}

int	write_cb(t_cb *cb, int fd)
{
  int	wl;
  char	*str;

  if ((str = get_cb(cb_taken(cb), cb)) == NULL)
    return (0);
  wl = write(fd, str, strlen(str));
  fill_cb(str + wl, strlen(str) - wl, cb);
  free(str);
  return (0);
}
