/*
** read_stdin.c for read_stdin in /home/lopez_t/PSU_2014_myirc/src_client
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Tue Apr  7 09:20:01 2015 Thibaut Lopez
** Last update Sun Apr 12 22:03:30 2015 Thibaut Lopez
*/

#include "client.h"

t_com	*ptr_to_stdin_function()
{
  t_com	*ptrs;

  ptrs = xmalloc(10 * sizeof(t_com));
  ptrs[0].com = "/server";
  ptrs[1].com = "/nick";
  ptrs[2].com = "/list";
  ptrs[3].com = "/join";
  ptrs[4].com = "/part";
  ptrs[5].com = "/users";
  ptrs[6].com = "/msg";
  ptrs[7].com = "/quit";
  ptrs[8].com = NULL;
  ptrs[0].ptr = my_server;
  ptrs[1].ptr = my_nick_stdin;
  ptrs[2].ptr = my_list;
  ptrs[3].ptr = my_join_stdin;
  ptrs[4].ptr = my_part_stdin;
  ptrs[5].ptr = my_users;
  ptrs[6].ptr = my_msg;
  ptrs[7].ptr = my_quit_stdin;
  ptrs[8].ptr = NULL;
  return (ptrs);
}

char	*priv_msg(char *gnl)
{
  int	i;
  char	*ret;

  if (strncmp(skip_delim(gnl, " \t\n\r"), "/msg", 4) != 0)
    return (gnl);
  i = 0;
  while (gnl[i] != 0 && strchr(" \t\n\r", gnl[i]) != NULL)
    i++;
  while (gnl[i] != 0 && strchr(" \t\n\r", gnl[i]) == NULL)
    i++;
  while (gnl[i] != 0 && strchr(" \t\n\r", gnl[i]) != NULL)
    i++;
  while (gnl[i] != 0 && strchr(" \t\n\r", gnl[i]) == NULL)
    i++;
  while (gnl[i] != 0 && strchr(" \t\n\r", gnl[i]) != NULL)
    i++;
  if (gnl[i] == 0)
    return (gnl);
  ret = xmalloc((strlen(gnl) + 2) * sizeof(char));
  strncpy(ret, gnl, i);
  ret[i] = ':';
  strcpy(ret + i + 1, gnl + i);
  ret[strlen(gnl) + 1] = 0;
  free(gnl);
  return (ret);
}

int	read_stdin(t_clt *data)
{
  int	i;
  int	ret;
  char	*gnl;
  char	**tok;
  t_com	*com;

  ret = 0;
  if ((gnl = read_cb(&data->stdin, 0)) == NULL)
    return (0);
  if ((skip_delim(gnl, " \t\n\r"))[0] != '/')
    return (my_message(data, gnl));
  gnl = priv_msg(gnl);
  tok = stwt(gnl, " \t\n\r");
  com = ptr_to_stdin_function();
  if (tok != NULL && (i = find_ptr(com, tok[0])) != -1)
    ret = com[i].ptr(data, tok);
  else if (tok != NULL)
    fprintf(stderr, "%s: Command not found\n", tok[0]);
  if (tok != NULL)
    free(tok);
  free(com);
  return (ret);
}
