/*
** malloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Adrien Maret
** Login   maret_a@epitech.eu
**
** Started on  Fri Feb 14 14:35:09 2014 Adrien Maret
** Last update Fri Feb 14 14:35:11 2014 Adrien Maret
*/

#include "client.h"

static int	send_file_info(t_client *client, t_msg *msg, int *size)
{
  char		buf[BUF_SIZE];
  t_stat	info;

  memset(buf, 0, BUF_SIZE);
  if (msg->arg[strlen(msg->arg) - 1] == '\n')
    msg->arg[strlen(msg->arg) - 1] = '\0';
  if (stat(msg->arg, &info) < 0)
    return (_warning("Can't get file info : %m\n", -1));
  *size = info.st_size;
  if (write(client->sock_fd, "put", 3) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  sprintf(buf, "%s %d", msg->arg, (int)info.st_size);
  if (write(client->sock_fd, buf, strlen(buf)) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  return (ISUCCESS);
}

static int	send_file(t_client *client, t_msg *msg, int size)
{
  char		*buf;
  int		fd;

  if (!(buf = malloc(sizeof(char) * (size + 1))))
    return (_error("Can't allocate memory : %m\n", -1));
  if ((fd = open(msg->arg, O_RDWR)) < 0)
    return (_warning("Can't open file : %m\n", -1));
  if (read(fd, buf, size) < 0)
    return (_warning("Can't read file : %m\n", -1));
  if (write(client->sock_fd, buf, strlen(buf)) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  free(buf);
  close(fd);
  return (ISUCCESS);
}

int		cmd_put(void *info, t_msg *msg)
{
  t_client	*client;
  char		buf[BUF_SIZE];
  int		size;

  client = (t_client*)info;
  if (!strlen(msg->arg))
    return (_warning("Usage : put <file>\n", -1));
  if (send_file_info(client, msg, &size) < 0)
    return (IWARNING);
  memset(buf, 0, BUF_SIZE);
  if (client_read_sock(client->sock_fd, buf, BUF_SIZE) < 0)
    return (_warning("Can't read on socket : %m\n", -1));
  if (strcmp(buf, "OK"))
    return (_warning("An error as occured on server\n", -1));
  if (send_file(client, msg, size) < 0)
    return (IWARNING);
  memset(buf, 0, BUF_SIZE);
  if (client_read_sock(client->sock_fd, buf, BUF_SIZE) < 0)
    return (_warning("Can't read on socket : %m\n", -1));
  if (strcmp(buf, "OK"))
    return (_warning("An error as occured on server\n", -1));
  printf("File %s successfully uploaded\n", msg->arg);
  return (ISUCCESS);
}

static int	receive_file(t_client *client, char *name, int size)
{
  int		fd;
  char		*buf;

  if (!(buf = malloc(sizeof(char) * size)))
    return (_error("Can't allocate memory : %m\n", -1));
  if (name[strlen(name) - 1] == '\n')
    name[strlen(name) - 1] = '\0';
  if ((fd = open(name,  O_CREAT | O_RDWR, U_RW)) < 0)
    return (_warning("Can't create file : %m\n", -1));
  if (read(client->sock_fd, buf, size) < 0)
    return (_error("Can't read on socket : %m\n", -1));
  if (write(fd, buf, size) < 0)
    return (_warning("Can't create file : %m\n", -1));
  if (write(client->sock_fd, "OK", 2) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  close(fd);
  free(buf);
  return (ISUCCESS);
}

int		cmd_get(void *info, t_msg *msg)
{
  t_client	*client;
  char		buf[BUF_SIZE];
  int		size;
  int		ret;

  client = (t_client*)info;
  memset(buf, 0, BUF_SIZE);
  if (!strlen(msg->arg))
    return (_warning("Usage : get <file>\n", -1));
  sprintf(buf, "get %s", msg->arg);
  if (write(client->sock_fd, buf, strlen(buf)) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  memset(buf, 0, BUF_SIZE);
  if (client_read_sock(client->sock_fd, buf, BUF_SIZE) < 0)
    return (_warning("Can't read on socket : %m\n", -1));
  if ((size = atoi(buf)) <= 0)
    return (_warning("File does not exist\n", -1));
  if (write(client->sock_fd, "OK", 2) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  if ((ret = receive_file(client, msg->arg, size)) < 0)
    return (ret);
  return (ISUCCESS);
}
