/*
** init_func.c for init_func in /home/lopez_t/PSU_2014_myirc/src_client
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Tue Apr  7 14:45:08 2015 Thibaut Lopez
** Last update Sun Apr 12 19:50:10 2015 Thibaut Lopez
*/

#include "client.h"

void	init_data(t_clt *data, char *nick, char *user)
{
  data->s = 2;
  data->ip = NULL;
  data->port = 0;
  data->nick = xstrdup((nick != NULL) ? nick : "defaut");
  data->user = xstrdup((user != NULL) ? user : "guest");
  data->channel = NULL;
  init_cb(&data->sock, 4096, sizeof(char));
  init_cb(&data->wcb, 4096, sizeof(char));
  init_cb(&data->stdin, 4096, sizeof(char));
}

void	data_free(t_clt *data)
{
  if (data->s > 2)
    close(data->s);
  if (data->ip != NULL)
    free(data->ip);
  free(data->nick);
  free(data->channel);
  free_cb(&data->sock);
  free_cb(&data->wcb);
  free_cb(&data->stdin);
}

void	set_fd(int s, t_bf *bf)
{
  FD_ZERO(&(bf->rbf));
  FD_SET(0, &(bf->rbf));
  if (s > 2)
    {
      FD_SET(s, &bf->rbf);
      FD_SET(s, &bf->wbf);
    }
}
