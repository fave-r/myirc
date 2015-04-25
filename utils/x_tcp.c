/*
** xfunctions.c for faistapute in /home/fave_r/rendu/PSU_2014_myftp/utils
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Mar 12 11:08:49 2015 romaric
** Last update Thu Apr  9 17:02:49 2015 Thibaut Lopez
*/

#include "my_irc.h"

int			clean_return(int fd, char *str)
{
  if (fd > 2)
    close(fd);
  fprintf(stderr, "%s\n", str);
  return (1);
}

int			init_socket()
{
  struct protoent	*pe;

  pe = getprotobyname("TCP");
  return (socket(AF_INET, SOCK_STREAM, pe->p_proto));
}

int			init_bind(int s, int *port)
{
  struct sockaddr_in	sin;
  socklen_t		len;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(*port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    return (-1);
  len = sizeof(sin);
  if (*port == 0)
    {
      if (getsockname(s, (struct sockaddr *)&sin, &len) == -1)
	return (-1);
      *port = ntohs(sin.sin_port);
    }
  return (0);
}

int			init_connect(int s, int port, char *id)
{
  struct sockaddr_in	sin;

  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(id);
  return (connect(s, (const struct sockaddr *)&sin, sizeof(sin)));
}
