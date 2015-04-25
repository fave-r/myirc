/*
** gnl.h for gnl in /home/lopez_t/PSU_2014_myftp/src
** 
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
** 
** Started on  Wed Mar 11 09:48:47 2015 Thibaut Lopez
** Last update Thu Apr  9 18:50:02 2015 Thibaut Lopez
*/

#ifndef	GNL_H
#define	GNL_H

#include <termios.h>
#include <term.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "my_irc.h"

char	*x_mem_malloc(int);
char	*cat_gnl_icanon(char *, char *);
char	**fill_touch();
void	tfree(char **);
int	set_term(struct termios *);
void	unset_term(struct termios *);
void	my_control_l(char **, char *);
void	my_backspace(char **, char *);
void	my_enter(char **, char *);
void	my_control_c(char **, char *);
int	my_puts(int);
char	*gnl_icanon(const int, int);

#endif
