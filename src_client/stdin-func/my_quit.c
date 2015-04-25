/*
** my_quit.c for my_quit in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 22:09:29 2015 Thibaut Lopez
*/

#include "client.h"

int	my_quit_stdin(t_clt *data, char **com)
{
  (void)com;
  if (data->s > 2)
    my_putstr("QUIT :Goodbye !\r\n", data->s);
  my_putstr("Goodbye !\n", 1);
  return (1);
}
