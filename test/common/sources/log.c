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

static char	*get_date(void)
{
  time_t	ts;
  char		*date;

  if (time(&ts) < 0)
    return (__warning("Can't get timestamp : %m\n", -1));
  date = ctime(&ts);
  date[strlen(date) - 1] = '\0';
  return (date);
}

int		add_log(char *s, int ctrl,  ...)
{
  static int	fd = -1;
  va_list	ap;
  char		buf[BUF_SIZE];
  char		*date;

  va_start(ap, ctrl);
  memset(buf, 0, BUF_SIZE);
  if (ctrl == 1)
    return (close(fd) ? IWARNING : ISUCCESS);
  if (fd < 0)
    {
      if ((fd = open(LOG_FILE, O_APPEND | O_CREAT | O_RDWR, U_RW)) < 0)
	return (_warning("Can't open log file : %m\n", -1));
      if (write(fd, "\n ---------------------------------- \n\n", 39) < 0)
	return (_warning("Can't write log output : %m\n", -1));
    }
  if (!(date = get_date()))
    return (IWARNING);
  if (sprintf(buf, "%s : ", date) < 0 || write(fd, buf, strlen(buf)) < 0)
    return (_warning("Can't write log output : %m\n", -1));
  memset(buf, 0, BUF_SIZE);
  if (vsprintf(buf, s, ap) < 0 || write(fd, buf, strlen(buf)) < 0)
    return (_warning("Can't write log output : %m\n", -1));
  va_end(ap);
  return (ISUCCESS);
}
