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

static int	print_welcome(t_handle *handle)
{
  char		buf[BUF_SIZE];

  memset(buf, 0, BUF_SIZE);
  sprintf(buf, "Welcome to FTP server !\nYour ip is : %s\n", handle->cli_ip);
  if (write(handle->cli_fd, buf, strlen(buf)) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  return (ISUCCESS);
}

static int	print_goodbye(t_handle *handle)
{
  if (write(handle->cli_fd, "Good bye !\n", 11) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  add_log("Close client %d socket\n", 0, handle->cli_num);
  if (close(handle->cli_fd) < 0)
    return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  add_log("Close server socket for client %d\n", 0, handle->cli_num);
  if (close(handle->socketfd) < 0)
    return (_error("Can't close socket fd (%d)\n", -1, handle->socketfd));
  add_log("Server for client %d successfully exit\n", 0, handle->cli_num);
  add_log("", 1);
  return (ISUCCESS);
}

int		server_read_sock(t_handle *handle, char *cmd)
{
  char		buf[BUF_SIZE];
  int		ret;

  memset(buf, 0, BUF_SIZE);
  if ((ret = read(handle->cli_fd, buf, BUF_SIZE)) > 0)
    memcpy(cmd, buf, ret);
  else if (ret < 0)
    return (_warning("Nothing to read on socket : %m\n", -1));
  return (ISUCCESS);
}

void	broken_pipe(int signum)
{
  (void)signum;
  add_log("Broken pipe when transferring file.\n", 0);
  add_log("", 1);
  exit(IERROR);
}

int		server_handle_client(t_handle *handle)
{
  t_msg		msg;
  char		cmd[BUF_SIZE];
  int		ret;
  int		flag;

  flag = 1;
  if (print_welcome(handle) < 0)
    return (IERROR);
  if (signal(SIGPIPE, &broken_pipe) == SIG_ERR)
    return (_error("Can't catch SIGPIPE : %m\n", -1));
  while (flag)
    {
      memset(cmd, 0, BUF_SIZE);
      server_read_sock(handle, cmd);
      if (read_command(cmd, &msg) < 0)
	return (IERROR);
      handle->timeout = 1;
      if ((ret = msg.fptr(handle, &msg)) == IERROR)
	return (IERROR);
      else if (ret == QUIT)
	flag = 0;
    }
  return (print_goodbye(handle));
}
