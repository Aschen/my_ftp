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

int		main(int ac, char **av)
{
  int		socketfd;
  int		flag;

  if (ac != 2)
    return (_warning("Usage : %s <port>\n", -1, av[0]));
  if (server_start(atoi(av[1]), &socketfd) < 0)
    return (IERROR);
  flag = MAX_CLIENT;
  while (flag)
    {
      server_accept(socketfd);
      flag--;
    }
  return (server_stop(socketfd));
}
