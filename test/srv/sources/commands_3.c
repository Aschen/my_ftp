/*
** malloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Adrien Maret
** Login   maret_a@epitech.eu
**
** Started on  Fri Feb 14 14:35:09 2014 Adrien Maret
** Last update Fri Feb 14 14:35:11 2014 Adrien Maret
*/

#include "server.h"

int		cmd_pwd(void *info, t_msg *msg)
{
  t_handle	*handle;
  char		buf[BUF_SIZE];

  (void)msg;
  handle = (t_handle*)info;
  add_log("Client %d execute command pwd\n", 0, handle->cli_num);
  memset(buf, 0, BUF_SIZE);
  sprintf(buf, "%s\n", handle->path);
  if (write(handle->cli_fd, buf, strlen(buf)) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  return (ISUCCESS);
}

int		cmd_quit(void *info, t_msg *msg)
{
  t_handle	*handle;

  (void)msg;
  handle = (t_handle*)info;
  add_log("Client %d execute command quit\n", 0, handle->cli_num);
  return (QUIT);
}

int		cmd_help(void *info, t_msg *msg)
{
  t_handle	*handle;

  (void)msg;
  handle = (t_handle*)info;
  add_log("Client %d execute command help\n", 0, handle->cli_num);
  if (write(handle->cli_fd, "", 1) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  return (ISUCCESS);
}
