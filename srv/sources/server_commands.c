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

int			get_command(char *tok)
{
  static const char	cmds[CMD_NB][CMD_SIZE] =
    { "help",
      "quit",
      "ls",
      "pwd",
      "cd",
      "get",
      "put"
    };
  int			i;

  i = -1;
  if (tok == NULL)
    return (IWARNING);
  if (tok[strlen(tok) - 1] == '\n')
    tok[strlen(tok) - 1] = '\0';
  while (++i < CMD_NB)
    if (strlen(tok) == strlen(cmds[i]))
      if (!strcmp(cmds[i], tok))
	return (i);
  return (_warning("Unknown command '%s'\n", -1, tok));
}

t_fptr			get_cmd(int cmd)
{
  static const t_fptr	cmds[CMD_NB] =
    { &cmd_help,
      &cmd_quit,
      &cmd_ls,
      &cmd_pwd,
      &cmd_cd,
      &cmd_get,
      &cmd_put
    };
  return (cmds[cmd]);
}

int			read_command(char *buf, t_msg *msg)
{
  char			*tok;
  char			*tmp;

  if (!(tmp = strdup(buf)))
    return (_error("Can't allocate memory : %m\n", -1));
  tok = strtok(tmp, " \t");
  if ((msg->cmd = get_command(tok)) < 0)
    return (IWARNING);
  memset(msg->arg, 0, ARG_SIZE);
  msg->fptr = NULL;
  tok = strtok(NULL, " \t");
  if (tok)
    memcpy(msg->arg, tok, ((strlen(tok) >= ARG_SIZE) ?
			   ARG_SIZE : strlen(tok) - 1));
  msg->fptr = get_cmd(msg->cmd);
  free(tmp);
  return (ISUCCESS);
}
