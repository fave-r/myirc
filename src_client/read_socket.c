/*
** read_socket.c for read_socket in /home/lopez_t/PSU_2014_myirc
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Thu Apr  9 15:45:23 2015 Thibaut Lopez
** Last update Sun Apr 12 20:35:59 2015 Thibaut Lopez
*/

#include "client.h"

t_com	*ptr_to_socket_function()
{
  t_com	*ptrs;

  ptrs = xmalloc(10 * sizeof(t_com));
  ptrs[0].com = "PRIVMSG";
  ptrs[1].com = "NOTICE";
  ptrs[2].com = "JOIN";
  ptrs[3].com = "PART";
  ptrs[4].com = "NICK";
  ptrs[5].com = "PING";
  ptrs[6].com = "ERROR";
  ptrs[7].com = "QUIT";
  ptrs[8].com = NULL;
  ptrs[0].ptr = my_privmsg;
  ptrs[1].ptr = my_notice;
  ptrs[2].ptr = my_join_socket;
  ptrs[3].ptr = my_part_socket;
  ptrs[4].ptr = my_nick_socket;
  ptrs[5].ptr = my_ping;
  ptrs[6].ptr = my_error;
  ptrs[7].ptr = my_quit;
  ptrs[8].ptr = NULL;
  return (ptrs);
}

int	read_socket(t_clt *data)
{
  int	i;
  int	ret;
  t_com	*com;
  char	*tmp;
  char	**tok;

  tmp = read_cb(&data->sock, data->s);
  if (tmp == NULL)
    return (0);
  com = ptr_to_socket_function();
  while (tmp != NULL)
    {
      tok = stwt(tmp, " \t\n");
      free(tmp);
      if (tok != NULL)
	{
	  i = find_ptr(com,
		       (tok[0][0] == ':' && tok[1] != NULL) ? tok[1] : tok[0]);
	  ret = (i == -1) ? my_code(data, tok) : com[i].ptr(data, tok);
	  free(tok);
	}
      tmp = get_line_cb(&data->sock);
    }
  free(com);
  return (ret);
}
