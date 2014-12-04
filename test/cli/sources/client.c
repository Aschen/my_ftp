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

int		client_start(t_client *client)
{
  t_protoent	*pe;

  client->sock_size = sizeof(client->sock_info);
  client->sock_info.sin_family = AF_INET;
  client->sock_info.sin_port = htons(client->port);
  client->sock_info.sin_addr.s_addr = inet_addr(client->ip);
  if (!(pe = getprotobyname("TCP")))
    return (_error("Can't get protocol : %m\n", -1));
  if ((client->sock_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) < 0)
    return (_error("Can't open socket : %m\n", -1));
  if (connect(client->sock_fd, (struct sockaddr*)&(client->sock_info)
	      , client->sock_size) < 0)
    return (_error("Can't connect to server : %m\n", client->sock_fd));
  return (ISUCCESS);
}

int		client_stop(t_client *client)
{
  if (close(client->sock_fd) < 0)
    return (_error("Can't close socket : %m\n", -1));
  return (ISUCCESS);
}
