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

int			cmd_ls(void *info, t_msg *msg)
{
  t_client	*client;
  char		buf[BUF_SIZE];

  (void)msg;
  client = (t_client*)info;
  memset(buf, 0, BUF_SIZE);
  if (write(client->sock_fd, "ls", 2) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  if (client_read_sock(client->sock_fd, buf, BUF_SIZE) >= 0)
    write(1, buf, strlen(buf));
  else
    return (_error("[ERROR]\nCan't reach the server : %m\n", -1));
  return (ISUCCESS);
}

int			cmd_pwd(void *info, t_msg *msg)
{
  t_client	*client;
  char		buf[BUF_SIZE];

  (void)msg;
  client = (t_client*)info;
  memset(buf, 0, BUF_SIZE);
  if (write(client->sock_fd, "pwd", 3) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  if (client_read_sock(client->sock_fd, buf, BUF_SIZE) >= 0)
    write(1, buf, strlen(buf));
  else
    return (_error("[ERROR]\nCan't reach the server : %m\n", -1));
  return (ISUCCESS);
}

int			cmd_quit(void *info, t_msg *msg)
{
  t_client	*client;
  char		buf[BUF_SIZE];

  (void)msg;
  client = (t_client*)info;
  memset(buf, 0, BUF_SIZE);
  if (write(client->sock_fd, "quit", 4) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  if (client_read_sock(client->sock_fd, buf, BUF_SIZE) >= 0)
    write(1, buf, strlen(buf));
  else
    return (_error("[ERROR]\nCan't reach the server : %m\n", -1));
  return (QUIT);
}

int			cmd_cd(void *info, t_msg *msg)
{
  t_client	*client;
  char		buf[BUF_SIZE];

  client = (t_client*)info;
  memset(buf, 0, BUF_SIZE);
  if (!strlen(msg->arg))
    return (_warning("Usage : cd <dir>\n", -1));
  strcat(buf, "cd ");
  strcat(buf, msg->arg);
  if (write(client->sock_fd, buf, strlen(buf)) < 0)
    return (_warning("Can't write on socket : %m\n", -1));
  memset(buf, 0, BUF_SIZE);
  if (client_read_sock(client->sock_fd, buf, BUF_SIZE) >= 0)
    write(1, buf, strlen(buf));
  else
    return (_error("[ERROR]\nCan't reach the server : %m\n", -1));
  return (ISUCCESS);
}

int			cmd_help(void *info, t_msg *msg)
{
  int			cmd;
  static const	char	hasht[CMD_NB][BUF_SIZE] =
    { " 'help' -> Display help",
      " 'quit' -> Exit the client",
      " 'ls' -> List file in server current directory",
      " 'pwd' -> Print current working directory",
      " 'cd' <dir> -> Change current directory",
      " 'get' <file> -> Download file",
      " 'put'<file> -> Upload file"
    };

  (void)info;
  if (!strlen(msg->arg))
    {
      printf("Available commands :\n quit help ls\n pwd cd get\n put\n");
      printf(" - Type 'help <command>' to open specific help\n");
      return (ISUCCESS);
    }
  if ((cmd = get_command(msg->arg)) < 0)
    return (_warning("Unknown command '%s'\n", -1, msg->arg));
  printf("%s\n", hasht[cmd]);
  return (ISUCCESS);
}
