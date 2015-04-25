/*
** circular_buffer.c for circular_buffer in /home/lopez_t/PSU_2014_myirc/utils/CircularBuffer
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Tue Apr  7 18:34:52 2015 Thibaut Lopez
** Last update Sat Apr 11 15:37:24 2015 Thibaut Lopez
*/

#include "my_irc.h"

int	init_cb(t_cb *cb, int cap, int sz)
{
  cb->buff = xmalloc((cap + 1) * sz);
  cb->cap = cap + 1;
  cb->sz = sz;
  cb->beg = 0;
  cb->end = 0;
  return (0);
}

void	free_cb(t_cb *cb)
{
  free(cb->buff);
}

void	*get_cb(int len, t_cb *cb)
{
  void	*buff;

  if (cb->beg == cb->end)
    return (NULL);
  else if (cb_taken(cb) < len)
    return (NULL);
  buff = xmalloc((len + 1) * cb->sz);
  bzero(buff, (len + 1) * cb->sz);
  if (cb->beg < cb->end || cb->cap - cb->beg >= len)
    memcpy(buff, cb_begin(cb), len * cb->sz);
  else
    {
      memcpy(buff, cb_begin(cb), (cb->cap - cb->beg) * cb->sz);
      memcpy((char *)buff + (cb->cap - cb->beg) * cb->sz,
	     cb->buff, (len - cb->cap + cb->beg) * cb->sz);
    }
  cb->beg += len;
  cb->beg %= cb->cap + 1;
  return (buff);
}

int	fill_cb(void *to_add, int len, t_cb *cb)
{
  if (cb_available(cb) < len)
    return (1);
  if (len < cb->cap - cb->end)
    memcpy(cb_end(cb), to_add, (len * cb->sz));
  else
    {
      memcpy(cb_end(cb), to_add, (cb->cap - cb->end) * cb->sz);
      memcpy(cb->buff, (char *)to_add + (cb->cap - cb->end) * cb->sz,
	     (len - cb->cap + cb->end) * cb->sz);
    }
  cb->end += len;
  cb->end %= cb->cap;
  return (0);
}

int	cbchr(t_cb *cb, void *c)
{
  int	i;

  i = cb->beg;
  while (i % cb->cap != cb->end &&
	 memcmp((char *)cb->buff + (i % cb->cap) * cb->sz, c, cb->sz) != 0)
    i++;
  if (i % cb->cap == cb->end)
    return (-1);
  return (i - cb->beg);
}
