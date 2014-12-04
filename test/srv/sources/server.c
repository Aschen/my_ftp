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

int		server_start(int port, int *socketfd)
{
  t_protoent	*pe;
  t_sockaddr	srv_in;

  add_log("Start FTP server\n", 0);
  if (!(pe = getprotobyname("TCP")))
    return (_error("Can't get protocol : %m\n", -1));
  add_log("Open TCP socket\n", 0);
  if ((*socketfd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    return (_error("Can't open socket : %m\n", -1));
  srv_in.sin_family = AF_INET;
  srv_in.sin_port = htons(port);
  srv_in.sin_addr.s_addr = INADDR_ANY;
  add_log("Bind socket to port %d for any ip addr\n", 0, port);
  if (port > 65535 || port < 1024)
    return (_error("The port must be between 1024 and 65535\n", -1));
  if (bind(*socketfd, (const struct sockaddr*)&srv_in, sizeof(srv_in)) < 0)
    return (_error("Can't bind socket to port %d : %m\n", *socketfd, port));
  add_log("Listen on socket (%d max clients)\n", 0, MAX_CLIENT);
  if (listen(*socketfd, MAX_CLIENT) < 0)
    return (_error("Can't listen on socket : %m\n", *socketfd));
  add_log("Server successfully initialized\n", 0);
  return (ISUCCESS);
}

int		server_accept(int socketfd)
{
  static int	client = 1;
  int		pid;
  t_handle	handle;

  handle.cli_in_size = sizeof(handle.cli_in);
  handle.cli_num = client++;
  handle.socketfd = socketfd;
  memcpy(handle.path, ".\0", 2);
  handle.path_lvl = 1;
  handle.cli_fd = accept(handle.socketfd
			       , (struct sockaddr *)&(handle.cli_in)
			 , &(handle.cli_in_size));
  if (handle.cli_fd < 0)
    return (EAGAIN);
  handle.cli_ip = inet_ntoa(handle.cli_in.sin_addr);
  add_log("New client connected from %s\n", 0, handle.cli_ip);
  if ((pid = fork()) < 0)
    return (_error("Can't fork : %m\n", handle.cli_fd));
  else if (pid == 0)
    exit(server_handle_client(&handle));
  if (close(handle.cli_fd) < 0)
    return (_warning("Can't close client file descriptor\n", -1));
  return (ISUCCESS);
}

int		server_stop(int socketfd)
{
  add_log("Stop FTP server\n", 0);
  add_log("Close socket before exit\n", 0);
  if (close(socketfd) < 0)
    return (_error("Can't close socketfd : %m\n", -1));
  add_log("Server successfully exit\n", 0);
  add_log("", 1);
  return (ISUCCESS);
}
