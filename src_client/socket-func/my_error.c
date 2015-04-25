/*
** my_error.c for my_error in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Sun Apr 12 19:29:59 2015 Thibaut Lopez
*/

#include "client.h"

int	my_error(t_clt *data, char **com)
{
  (void)data;
  my_putstr("Error", 1);
  if (com[1] != NULL)
    {
      my_putstr(": ", 1);
      my_putstr(com[1], 1);
    }
  my_putstr("\n", 1);
  return (1);
}
