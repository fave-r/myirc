/*
** my_server.c for my_server in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 20:30:41 2015 Thibaut Lopez
*/

#include "client.h"

int	error_return(int s, char **to_free, char *err, int ret)
{
  fprintf(stderr, "%s\n", err);
  if (s > 2)
    close(s);
  free(to_free);
  return (ret);
}

int	create_connexion(t_clt *data, char **iprt)
{
  int	s;
  int	port;

  if ((port = my_strtol((iprt[1] == NULL) ? "6667" : iprt[1])) == -1)
    return (error_return(-1, iprt, "Not a good port", 1));
  if ((s = init_socket()) == -1)
    return (error_return(-1, iprt, "Couldn't create a new socket", 1));
  if (init_connect(s, port, iprt[0]) == -1)
    return (error_return(s, iprt, "Couldn't connect", 1));
  if (data->s > 2)
    close(data->s);
  data->s = s;
  if (data->ip != NULL)
    free(data->ip);
  data->ip = strdup(iprt[0]);
  data->port = port;
  return (0);
}

int	my_server(t_clt *data, char **com)
{
  char	*nick[3];
  char	**iprt;

  if (handle_args(com, 2, 2, 1) == 1)
    return (0);
  iprt = stwt(com[1], ":");
  if (handle_args(iprt, 1, 2, 0) == 1)
    return (error_return(-1, iprt, "Wrong argument", 1));
  if (create_connexion(data, iprt) == 1)
    return (0);
  printf("Connected to %s from port %d\n", data->ip, data->port);
  fill_cb("HELLO\r\n", 7, &data->wcb);
  nick[0] = "/nick";
  nick[1] = data->nick;
  nick[2] = NULL;
  my_nick_stdin(data, nick);
  fill_cb("USER ", 5, &data->wcb);
  fill_cb(data->user, strlen(data->user), &data->wcb);
  fill_cb(" 8 * :C IRC Client\r\n", 20, &data->wcb);
  return (0);
}
