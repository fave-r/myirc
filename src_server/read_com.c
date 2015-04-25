/*
** read_com.c for in_real_context in /home/fave_r/rendu/PSU_2014_myirc/src_server
**
** Made by romaric
** Login   <fave_r@epitech.net>
**
** Started on  Thu Apr  9 09:45:58 2015 romaric
** Last update Wed Apr 22 14:31:27 2015 Thibaut Lopez
*/

#include "server.h"

void		assign_ptrs(t_com *ptrs)
{
  ptrs[0].ptr = my_nick;
  ptrs[1].ptr = my_list;
  ptrs[2].ptr = my_join;
  ptrs[3].ptr = my_part;
  ptrs[4].ptr = my_user;
  ptrs[5].ptr = my_users;
  ptrs[6].ptr = my_msg;
  ptrs[7].ptr = my_hello;
  ptrs[8].ptr = my_send_file;
  ptrs[9].ptr = my_accept_file;
  ptrs[10].ptr = my_ping;
  ptrs[11].ptr = my_pong;
  ptrs[12].ptr = my_quit;
  ptrs[13].ptr = NULL;

}

t_com		*ptr_to_function()
{
  t_com		*ptrs;

  ptrs = xmalloc(14 * sizeof(t_com));
  ptrs[0].com = "NICK";
  ptrs[1].com = "LIST";
  ptrs[2].com = "JOIN";
  ptrs[3].com = "PART";
  ptrs[4].com = "USER";
  ptrs[5].com = "NAMES";
  ptrs[6].com = "PRIVMSG";
  ptrs[7].com = "HELLO";
  ptrs[8].com = "SEND_FILE";
  ptrs[9].com = "ACCEPT_FILE";
  ptrs[10].com = "PING";
  ptrs[11].com = "PONG";
  ptrs[12].com = "QUIT";
  ptrs[13].com = NULL;
  assign_ptrs(ptrs);
  return (ptrs);
}

int		read_com(t_user *data, t_chan *chans)
{
  char		*gnl;
  char		**tok;
  t_com		*com;
  int		i;
  int		ret;

  ret = 0;
  gnl = read_cb(&data->cb, data->fd);
  while (gnl != NULL)
    {
      printf("%s\n", gnl);
      if ((tok = stwt(gnl, " \t\n\r")) == NULL)
	return (0);
      com = ptr_to_function();
      i = find_ptr(com, tok[0]);
      if (i != -1)
	ret = com[i].ptr(data, tok, chans);
      else
	fill_cb("421 : unknown command\r\n", 23, &data->wr);
      free(tok);
      free(com);
      free(gnl);
      gnl = get_line_cb(&data->cb);
    }
  return (ret);
}
