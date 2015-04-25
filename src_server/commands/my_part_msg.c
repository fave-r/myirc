/*
** my_part_msg.c for inrealcontext in /home/fave_r/rendu/PSU_2014_myirc
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Sun Apr 12 21:30:44 2015 romaric
** Last update Sun Apr 12 21:33:53 2015 romaric
*/

#include "server.h"

t_chan		*put_part_erro(t_user *data, char *com)
{
  char		str[512];

  bzero(str, 512);
  sprintf(str, "442 %s :You're not on that channel\r\n", com);
  fill_cb(str, strlen(str), &data->wr);
  return (NULL);
}
