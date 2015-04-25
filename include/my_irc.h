/*
** my_irc.h for my_irc in /home/lopez_t/PSU_2014_myirc
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Mon Apr  6 16:32:10 2015 Thibaut Lopez
** Last update Sun Apr 12 19:32:14 2015 Thibaut Lopez
*/

#ifndef	MY_IRC_H
#define	MY_IRC_H
#define	BUFF_SIZE	1028

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>

typedef struct	s_com
{
  char		*com;
  int		(*ptr)();
}		t_com;

typedef struct	s_fd
{
  int		fd;
  struct s_fd	*next;
  struct s_fd	*prev;
}		t_fd;

typedef struct	s_bf
{
  fd_set	rbf;
  fd_set	wbf;
}		t_bf;

typedef struct	s_cb
{
  void		*buff;
  int		cap;
  int		sz;
  int		beg;
  int		end;
}		t_cb;

int	my_putstr(char *, int);
int	my_strstr(char **, char *);
char	*my_strcat(char *, char *);
char	*get_next_line(const int);
int	find_ptr(t_com *, char *);
int	my_strtol(char *);
char	**sfree(char **);
int	sstrlen(char **);
char	**sstrcat(char **, char *);
char	*skip_delim(char *, char *);
char	**stwt(char *, char *);
int	xopen(const char *, int);
ssize_t	xread(int, void *, size_t);
void	*xmalloc(size_t);
char	*xstrdup(const char *);
int	init_cb(t_cb *, int, int);
void	free_cb(t_cb *);
void	*get_cb(int, t_cb *);
int	fill_cb(void *, int, t_cb *);
int	cbchr(t_cb *, void *);
char	*get_line_cb(t_cb *);
char	*read_cb(t_cb *, int);
int	write_cb(t_cb *, int);
int	cb_taken(t_cb *);
int	cb_available(t_cb *);
void	*cb_begin(t_cb *);
void	*cb_end(t_cb *);
int	clean_return(int, char *);
int	init_socket();
int	init_bind(int, int *);
int	init_connect(int, int, char *);

#endif
