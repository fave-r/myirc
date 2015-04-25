/*
** client.c for client in /home/lopez_t/PSU_2014_myirc
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 16:29:38 2015 Thibaut Lopez
** Last update Tue Apr 21 19:16:36 2015 Thibaut Lopez
*/

#include "client.h"

static int		quit_sig = 0;

void			signal_quit(__attribute__((unused))int signo)
{
  quit_sig = 1;
  write(1, "\n", 1);
}

int			isset_fds(t_clt *data, t_bf *bf, int bool)
{
  if (data->s > 2 && FD_ISSET(data->s, &bf->rbf))
    bool = read_socket(data);
  if (data->s > 2 && FD_ISSET(data->s, &bf->wbf))
    bool = write_cb(&data->wcb, data->s);
  if (FD_ISSET(0, &bf->rbf))
    bool = read_stdin(data);
  return (bool);
}

int			handle_fds(t_clt *data)
{
  t_bf			bf;
  int			bool;
  int			nb_client;
  struct timeval	tv;

  nb_client = 1;
  bool = 0;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  while (bool == 0)
    {
      if (quit_sig == 1)
	return (0);
      set_fd(data->s, &bf);
      if ((bool = select(data->s + nb_client, &bf.rbf, NULL, NULL, &tv)) != -1)
	bool = isset_fds(data, &bf, bool);
    }
  return (0);
}

int			main(int argc, char **argv)
{
  t_clt			data;

  if (argc > 4)
    {
      printf("Usage: ./client [ip[:port]] [nick] [user]\n");
      return (1);
    }
  init_data(&data, (argc > 2) ? argv[2] : NULL, (argc > 3) ? argv[3] : NULL);
  printf("Welcome to this client!\n");
  if (argc >= 2)
    {
      argv[2] = NULL;
      my_server(&data, argv);
    }
  signal(SIGINT, signal_quit);
  handle_fds(&data);
  data_free(&data);
  return (0);
}
