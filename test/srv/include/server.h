/*
** malloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Adrien Maret
** Login   maret_a@epitech.eu
**
** Started on  Fri Feb 14 14:35:09 2014 Adrien Maret
** Last update Fri Feb 14 14:35:11 2014 Adrien Maret
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "ftp.h"

# ifdef LOG_FILE
#  undef LOG_FILE
#  define LOG_FILE		"server_access.log"
# endif

# define MAX_CLIENT		10

typedef				struct	s_handle
{
  int				socketfd;
  int				cli_fd;
  t_sockaddr			cli_in;
  socklen_t			cli_in_size;
  int				cli_num;
  char				*cli_ip;
  char				path[PATH_SIZE];
  int				path_lvl;
  int				timeout;
}				t_handle;

int				server_read_sock(t_handle *handle, char *cmd);
int				server_handle_client(t_handle *handle);

int				server_start(int port, int *socketfd);
int				server_stop(int socketfd);
int				server_accept(int socketfd);

int				read_command(char *buf, t_msg *msg);

#endif /* !_SERVER_H_ */
