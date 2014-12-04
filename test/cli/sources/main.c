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

int		main(int ac, char **av) // RELINK !!
{
  t_client	client;

  if (ac != 3)
    return (_warning("Usage : %s <ip> <port>\n", -1, av[0]));
  client.ip = av[1];
  client.port = atoi(av[2]);
  if (client_start(&client) < 0)
    return (IERROR);
  client_handle(&client);
  client_stop(&client);
  return (ISUCCESS);
}
