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

static int	get_file_info(t_handle *handle, int *size, char *name)
{
  t_stat	info;
  char		buf[BUF_SIZE];

  memset(buf, 0, BUF_SIZE);
  if (name[strlen(name) - 1] == '\n')
    name[strlen(name) - 1] = '\0';
  if (stat(name, &info) < 0)
    return (_warning("Can't get file info : %m\n", -1));
  *size = info.st_size;
  sprintf(buf, "%d", (int)info.st_size);
  if (write(handle->cli_fd, buf, strlen(buf)) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  memset(buf, 0, BUF_SIZE);
  if (server_read_sock(handle, buf) < 0)
    return (IWARNING);
  if (!strncmp(buf, "OK", 2))
    return (ISUCCESS);
  return (IWARNING);
}

static int	receive_file(t_handle *handle, char *path, int size, t_msg *msg)
{
  char		*buf;
  int		fd;

  if (!(buf = malloc(sizeof(char) * size)))
    return (_error("Can't allocate memory : %m\n", -1));
  if ((fd = open(path, O_RDWR)) < 0)
    return (_warning("Can't open file : %m\n", -1));
  if (read(fd, buf, size) < 0)
    return (_warning("Can't read file : %m\n", -1));
  if (write(handle->cli_fd, buf, size) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  if (server_read_sock(handle, buf) < 0)
    return (IWARNING);
  if (!strncmp(buf, "OK", 2))
    add_log("File %s successfully send to client %d\n", 0, msg->arg
	    , handle->cli_num);
  else
    add_log("Fail to send file %s to client %d\n", 0, msg->arg
	    , handle->cli_num);
  free(buf);
  close(fd);
  return (ISUCCESS);
}

int		cmd_get(void *info, t_msg *msg)
{
  t_handle	*handle;
  char		path[PATH_SIZE];
  int		size;

  handle = (t_handle*)info;
  memset(path, 0, PATH_SIZE);
  add_log("Client %d execute command get %s\n", 0, handle->cli_num, msg->arg);
  strcat(path, handle->path);
  strcat(path, "/");
  strcat(path, msg->arg);
  if (get_file_info(handle, &size, path) < 0)
    if (write(handle->cli_fd, "0", 1) < 0)
      return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  if (receive_file(handle, path, size, msg) < 0)
    return (IWARNING);
  return (ISUCCESS);
}
