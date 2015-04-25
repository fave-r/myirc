/*
** clone.c for inrealcontext in /home/fave_r/rendu/PSU_2014_myirc/src_server
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Sat Apr 11 16:34:00 2015 romaric
** Last update Sat Apr 11 19:30:38 2015 romaric
*/

#include "server.h"

void	clone_us(t_user *user, t_cln **clone)
{
  (*clone) = xmalloc(sizeof(t_cln));
  (*clone)->next = NULL;
  (*clone)->prev = NULL;
  (*clone)->nick = xstrdup(user->nick);
  (*clone)->fd = user->fd;
}
