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

int		client_read_sock(int sock_dest, char *buf, int size)
{
  int		ret;

  memset(buf, 0, size);
  ret = read(sock_dest, buf, size);
  return ((ret >= 0) ? ret : IWARNING);
}

void	broken_pipe(int signum)
{
  (void)signum;
  add_log("Broken pipe when transferring file.\n", 0);
  add_log("", 1);
  exit(IERROR);
}

int		client_handle(t_client *client)
{
  int		ret;
  t_msg		msg;
  char		buf[BUF_SIZE];

  if (signal(SIGPIPE, &broken_pipe) == SIG_ERR)
    return (_error("Can't catch SIGPIPE : %m\n", -1));
  client_read_sock(client->sock_fd, buf, BUF_SIZE);
  printf("%s\n", buf);
  while (1)
    {
      write(1, PROMPT, PROMPT_SIZE);
      memset(buf, 0, BUF_SIZE);
      if (read(0, buf, BUF_SIZE) < 0)
	return (_error("Can't read on stdin : %m\n", -1));
      if ((ret = read_command(buf, &msg)) >= 0 && msg.cmd >= HELP)
	{
	  if ((ret = msg.fptr(client, &msg)) == IERROR)
	    return (IERROR);
	  else if (ret == QUIT)
	    return (ISUCCESS);
	}
      else if (ret == IERROR)
	return (IERROR);
    }
  return (ISUCCESS);
}
