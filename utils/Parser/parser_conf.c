/*
** parser_conf.c for parser_conf in /home/lopez_t/PSU_2014_myftp/src/src-serveur/Parser
**
** Made by Thibaut Lopez
** Login   <lopez_t@epitech.net>
**
** Started on  Sun Mar 22 15:56:23 2015 Thibaut Lopez
** Last update Fri Apr 10 18:34:45 2015 romaric
*/

#include "parser.h"

char		*my_substr(char *line, char *tag, char *def)
{
  int		i;

  i = 0;
  line += strlen(tag);
  while (strlen(line) - i > strlen(tag + 1)
	 && strncmp(line + i, tag + 1, strlen(tag + 1)) != 0)
    i++;
  if (strlen(line) - i > strlen(tag + 1))
    return (strndup(line, i - 2));
  return (xstrdup(def));
}

int		get_next_tag(int i, char **file, char *tag)
{
  int		j;
  size_t	len;

  while (file != NULL && file[i] != NULL)
    {
      j = 0;
      len = strlen(tag);
      while (strlen(file[i]) - j > len && strncmp(file[i] + j, tag, len) != 0)
	j++;
      if (strlen(file[i]) - j > len)
	return (i);
      i++;
    }
  return (-1);
}

char		*find_good_tag(char *tag, char *line, char *end)
{
  char		*ret;
  int		i;

  i = 0;
  while (strlen(line) - i > strlen(tag)
	 && strncmp(line + i, tag, strlen(tag)) != 0)
    i++;
  if (strlen(line) - i > strlen(tag))
    ret = my_substr(line + i, tag, "");
  else
    {
      i = 0;
      while (strlen(line) - i > strlen(end) &&
	     strncmp(line + i, end, strlen(end)) != 0)
	i++;
      if (strlen(line) - i > strlen(end))
	ret = xstrdup("");
      else
	ret = NULL;
    }
  return (ret);
}

char		*find_info(char *tag, char *end, char **file, int i)
{
  char		*ret;

  while (file[i] != NULL)
    {
      if ((ret = find_good_tag(tag, file[i], end)) != NULL)
	return (ret);
      i++;
    }
  return (xstrdup(""));
}

char		**get_file(char *file)
{
  FILE		*fd;
  char		*line;
  size_t	len;
  char		**ret;

  fd = fopen(file, "r");
  if (fd == NULL)
    return (NULL);
  ret = NULL;
  line = NULL;
  while (getline(&line, &len, fd) != -1)
    {
      ret = sstrcat(ret, line);
      line = NULL;
    }
  free(line);
  fclose(fd);
  return (ret);
}
