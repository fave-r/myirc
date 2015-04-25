/*
** parser.h for parser in /home/lopez_t/PSU_2014_myftp/include
**
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
**
** Started on  Sun Mar 22 15:55:19 2015 Thibaut Lopez
** Last update Wed Apr 22 14:02:34 2015 Thibaut Lopez
*/

#ifndef	PARSER_H
#define	PARSER_H

#include "my_irc.h"

typedef struct	s_user
{
  int		fd;
  char		*nick;
  char		*ip;
  t_cb		cb;
  t_cb		wr;
  int		usered;
  char		*username;
  char		*realname;
  int		nicked;
  int		chan;
  int		joined;
  int		tokill;
  struct s_user	*next;
  struct s_user	*prev;
}		t_user;

typedef struct	s_cln
{
  int		fd;
  char		*nick;
  struct s_cln	*next;
  struct s_cln	*prev;
}		t_cln;

typedef struct	s_chan
{
  int		id;
  char		*name;
  char		*pass;
  t_cln		*users;
  struct s_chan	*next;
  struct s_chan	*prev;
}		t_chan;

t_chan		*circular_linked_channel();
t_chan		*unit_chan_free(t_chan *);
t_chan		*channels_free(t_chan *);
char		*my_substr(char *, char *, char *);
int		get_next_tag(int, char **, char *);
char		*find_good_tag(char *, char *, char *);
char		*find_info(char *, char *, char **, int);
char		**get_file(char *);
char		**sfree(char **);

#endif
