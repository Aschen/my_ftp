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

static int	receive_file_info(t_handle *handle, int *size, char *name)
{
  char		buf[BUF_SIZE];
  char		*tok;

  if (server_read_sock(handle, buf) < 0)
    return (IWARNING);
  tok = strtok(buf, " ");
  memcpy(name, tok, strlen(tok));
  tok = strtok(NULL, " ");
  *size = atoi(tok);
  if (*size <= 0)
    return (_warning("Invalid size\n", -1));
  return (ISUCCESS);
}

static int	receive_file(t_handle *handle, int size, char *name)
{
  char		path[PATH_SIZE + BUF_SIZE];
  char		*buf;
  int		fd;

  if (!(buf = malloc(sizeof(char) * size)))
    return (_error("Can't allocate memory : %m\n", -1));
  if (read(handle->cli_fd, buf, size) < 0)
    return (_error("Can't read on client socket : %m\n", -1));
  memset(path, 0, PATH_SIZE + BUF_SIZE);
  strcat(path, handle->path);
  strcat(path, "/");
  strcat(path, name);
  if ((fd = open(path, O_CREAT | O_RDWR, U_RW)) < 0)
    return (_warning("Can't create file : %m\n", -1));
  if (write(fd, buf, size) < 0)
    return (_warning("Can't create file : %m\n", -1));
  close(fd);
  free(buf);
  return (ISUCCESS);
}

int		cmd_put(void *info, t_msg *msg)
{
  t_handle	*handle;
  int		ret;
  int		size;
  char		name[BUF_SIZE];

  handle = (t_handle*)info;
  memset(name, 0, BUF_SIZE);
  add_log("Client %d execute command put %s\n", 0, handle->cli_num, msg->arg);
  if ((ret = receive_file_info(handle, &size, name)) < 0)
    return (ret);
  if (write(handle->cli_fd, "OK", 2) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  if ((ret = receive_file(handle, size, name)) < 0)
    return (ret);
  if (write(handle->cli_fd, "OK", 2) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  add_log("Client %d create file %s of size %d\n", 0, handle->cli_num, msg->arg
	  , size);
  return (ISUCCESS);
}

