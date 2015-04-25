/*
** circular_linked_channel.c for circular_linked_channel in /home/lopez_t/PSU_2014_myftp/src/src-serveur/Parser
**
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
**
** Started on  Thu Mar 19 18:44:59 2015 Thibaut Lopez
** Last update Sat Apr 11 17:45:54 2015 romaric
*/

#include "parser.h"

t_chan		*new_channel(int i, char **file, t_chan *prev)
{
  char		*str;
  t_chan	*channel;
  static int	n = 0;

  channel = xmalloc(sizeof(t_chan));
  str = find_info("<name>", "</channel>", file, i);
  if (strlen(str) == 0)
    {
      free(str);
      free(channel);
      return (prev);
    }
  channel->name = my_strcat("#", str);
  free(str);
  channel->pass = find_info("<pass>", "</channel>", file, i);
  channel->users = NULL;
  channel->prev = prev;
  channel->id = n;
  if (prev != NULL)
    prev->next = channel;
  n++;
  return (channel);
}

t_chan		*base_channel()
{
  t_chan	*channel;

  channel = xmalloc(sizeof(t_chan));
  channel->name = xstrdup("#all");
  channel->pass = xstrdup("");
  channel->users = NULL;
  channel->prev = NULL;
  return (channel);
}

t_chan		*circular_linked_channel()
{
  int		i;
  t_chan	*beg;
  t_chan	*channels;
  char		**file;

  i = 0;
  beg = base_channel();
  channels = beg;
  file = get_file("conf/channel.conf");
  while ((i = get_next_tag(i, file, "<channel>")) != -1)
    {
      channels = new_channel(i, file, channels);
      i++;
    }
  if (channels != NULL && beg != NULL)
    {
      channels->next = beg;
      beg->prev = channels;
    }
  sfree(file);
  return (beg);
}

t_chan		*unit_chan_free(t_chan *to_free)
{
  t_chan	*ret;

  ret = NULL;
  if (to_free != NULL)
    {
      if (to_free->next != to_free)
	{
	  ret = to_free->next;
	  if (to_free->prev != NULL)
	    to_free->prev->next = ret;
	  if (ret != NULL)
	    ret->prev = to_free->prev;
	}
      free(to_free->name);
      free(to_free->pass);
      free(to_free);
    }
  return (ret);
}

t_chan		*channels_free(t_chan *channels)
{
  while (channels != NULL)
    channels = unit_chan_free(channels);
  return (NULL);
}
