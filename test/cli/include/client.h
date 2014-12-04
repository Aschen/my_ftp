/*
** malloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Adrien Maret
** Login   maret_a@epitech.eu
**
** Started on  Fri Feb 14 14:35:09 2014 Adrien Maret
** Last update Fri Feb 14 14:35:11 2014 Adrien Maret
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include "ftp.h"

# ifdef LOG_FILE
#  undef LOG_FILE
#  define LOG_FILE		"client_session.log"
# endif

# define PROMPT			"ftp> "
# define PROMPT_SIZE		5

typedef				struct s_client
{
  int				sock_fd;
  t_sockaddr			sock_info;
  socklen_t			sock_size;
  char				*ip;
  int				port;
}				t_client;

int				client_read_sock(int, char *, int);
int				client_handle(t_client *client);

int				client_stop(t_client *client);
int				client_start(t_client *client);

int				get_command(char *tok);
int				read_command(char *, t_msg *);

#endif /* !_CLIENT_H_ */
