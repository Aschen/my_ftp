/*
** malloc.c for malloc in /home/bovier_m/rendu/PSU_2013_malloc
**
** Made by Adrien Maret
** Login   maret_a@epitech.eu
**
** Started on  Fri Feb 14 14:35:09 2014 Adrien Maret
** Last update Fri Feb 14 14:35:11 2014 Adrien Maret
*/

#ifndef FTP_H_
# define FTP_H_

# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <pthread.h>

# define U_RW			(S_IWUSR | S_IRUSR)
# define LOG_FILE		"log.log"

# define BUF_SIZE		128
# define ARG_SIZE		128
# define PATH_SIZE		256

# define CMD_NB			7
# define CMD_SIZE		16

# define ISUCCESS		0
# define IWARNING		-1
# define IERROR			-2

# define PSUCCESS		((void*)1)
# define PWARNING		NULL
# define PERROR			NULL

typedef struct stat		t_stat;
typedef struct dirent		t_dirent;
typedef struct protoent		t_protoent;
typedef struct sockaddr_in	t_sockaddr;
typedef struct s_msg		t_msg;

typedef int			(*t_fptr)(void*, t_msg*);

struct				s_msg
{
  int				cmd;
  char				arg[ARG_SIZE];
  t_fptr			fptr;
};

typedef				enum e_cmd
  {
    HELP = 0,
    QUIT,
    LS,
    PWD,
    CD,
    GET,
    PUT
  }				t_cmd;

int				add_log(char *s, int ctrl, ...);

int				_error(char *s, int fd, ...);
int				_warning(char *s, int fd, ...);
void				*__error(char *s, int fd, ...);
void				*__warning(char *s, int fd, ...);

int				cmd_ls(void *info, t_msg *msg);
int				cmd_pwd(void *info, t_msg *msg);
int				cmd_quit(void *info, t_msg *msg);
int				cmd_cd(void *info, t_msg *msg);
int				cmd_help(void *info, t_msg *msg);

int				cmd_put(void *info, t_msg *msg);
int				cmd_get(void *info, t_msg *msg);

#endif /* !_FTP_H_ */
