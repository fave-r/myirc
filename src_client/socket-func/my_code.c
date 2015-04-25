/*
** my_code.c for my_code in /home/lopez_t/PSU_2014_myirc/src_client/commands
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 18:51:56 2015 Thibaut Lopez
** Last update Wed Apr 22 16:32:47 2015 Thibaut Lopez
*/

#include "client.h"

void	check_error(t_clt *data, char *err)
{
  if (strcmp(err, "403") == 0)
    {
      if (data->channel != NULL)
	free(data->channel);
      data->channel = NULL;
    }
}

int	my_code(t_clt *data, char **com)
{
  int	i;

  i = (com[0][0] == ':' && com[1] != NULL) ? 1 : 0;
  if (strlen(com[i]) > 3 || com[i][0] < '0' || com[i][0] > '9'
      || com[i][1] < '0' || com[i][1] > '9' || com[i][2] < '0'
      || com[i][2] > '9')
    {
      fprintf(stderr, "%s: command not found\n", com[i]);
      return (0);
    }
  printf("Answer: %s: ", com[i]);
  while (com[++i] != NULL && com[i][0] != ':')
    printf("%s ", com[i]);
  if (com[i] != NULL)
    printf("%s", com[i] + 1);
  printf("\n");
  check_error(data, (com[0][0] == ':' && com[1] != NULL) ? com[1] : com[0]);
  return (0);
}
