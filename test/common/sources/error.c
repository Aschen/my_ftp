/*
** malloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Adrien Maret
** Login   maret_a@epitech.eu
**
** Started on  Fri Feb 14 14:35:09 2014 Adrien Maret
** Last update Fri Feb 14 14:35:11 2014 Adrien Maret
*/

#include "ftp.h"

int		_error(char *s, int fd, ...)
{
  va_list	ap;
  char		buf[BUF_SIZE];

  va_start(ap, fd);
  memset(buf, 0, BUF_SIZE);
  vsprintf(buf, s, ap);
  fprintf(stderr, buf);
  add_log(buf, 0);
  va_end(ap);
  if (fd >= 0)
    close(fd);
  return (IERROR);
}

int		_warning(char *s, int fd, ...)
{
  va_list	ap;

  va_start(ap, fd);
  vfprintf(stderr, s, ap);
  va_end(ap);
  if (fd >= 0)
    close(fd);
  return (IWARNING);
}

void		*__error(char *s, int fd, ...)
{
  va_list	ap;
  char		buf[BUF_SIZE];

  va_start(ap, fd);
  memset(buf, 0, BUF_SIZE);
  vsprintf(buf, s, ap);
  fprintf(stderr, buf);
  add_log(buf, 0);
  va_end(ap);
  if (fd >= 0)
    close(fd);
  return (PERROR);
}

void		*__warning(char *s, int fd, ...)
{
  va_list	ap;

  va_start(ap, fd);
  vfprintf(stderr, s, ap);
  va_end(ap);
  if (fd >= 0)
    close(fd);
  return (PWARNING);
}

