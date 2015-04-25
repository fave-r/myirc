/*
** port_func.c for port_func in /home/lopez_t/PSU_2014_myftp/src/src-client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Tue Mar 17 17:43:09 2015 Thibaut Lopez
** Last update Mon Apr  6 17:08:47 2015 Thibaut Lopez
*/

#include "my_irc.h"

int	read_ip(char *mess, char *ip[20])
{
  int	i;
  int	j;
  char	*tok;

  i = 0;
  j = 0;
  tok = strtok(mess, ",");
  while (j < 4 && tok != NULL)
    {
      if (strlen(tok) > 3)
	return (-1);
      strcpy(*ip + i, tok);
      i += strlen(tok);
      (*ip)[i] = '.';
      j++;
      if (j < 4)
	{
	  i++;
	  tok = strtok(NULL, ",");
	}
    }
  (*ip)[i] = 0;
  if (tok == NULL)
    return (-1);
  return (0);
}

int	read_port(int *port)
{
  char	*tok1;
  char	*tok2;

  tok1 = strtok(NULL, ",");
  tok2 = strtok(NULL, ",");
  if (tok1 == NULL || tok2 == NULL)
    return (-1);
  *port = atoi(tok1) * 256 + atoi(tok2);
  return (0);
}

int	read_ip_and_port(char *mess, char *ip[20], int bool)
{
  int	port;
  char	*close;
  char	*tmp;

  tmp = (bool == 0) ? strchr(mess, '(') : mess;
  if (tmp == NULL)
    return (-1);
  if (bool == 0)
    {
      tmp++;
      if ((close = strchr(tmp, ')')) == NULL)
	return (-1);
      close[0] = 0;
    }
  if (read_ip(tmp, ip) == -1)
    return (-1);
  if (read_port(&port) == -1)
    return (-1);
  if (strtok(NULL, ",") != NULL)
    return (-1);
  return (port);
}
