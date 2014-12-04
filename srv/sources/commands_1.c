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

static int	my_ls(t_handle *handle, char *buf)
{
  t_dirent	*info;
  DIR		*dirp;

  if (!(dirp = opendir(handle->path)))
    return (_warning("Can't open %s : %m\n", -1, handle->path));
  while ((info = readdir(dirp)))
    {
      if (strcmp(info->d_name, ".") && strcmp(info->d_name, ".."))
	if (strlen(buf) + strlen(info->d_name) + 1 < BUF_SIZE)
	  {
	    strcat(buf, info->d_name);
	    strcat(buf, "\n");
	  }
    }
  closedir(dirp);
  return (ISUCCESS);
}

int		cmd_ls(void *info, t_msg *msg)
{
  t_handle	*handle;
  char		buf[BUF_SIZE];

  (void)msg;
  handle = (t_handle*)info;
  add_log("Client %d execute command ls\n", 0, handle->cli_num);
  memset(buf, 0, BUF_SIZE);
  if (my_ls(handle, buf) < 0)
    {
      memset(buf, 0, BUF_SIZE);
      sprintf(buf, "An error as occured : %m\n");
      if (write(handle->cli_fd, buf, strlen(buf)) < 0)
	return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
    }
  else
    if (write(handle->cli_fd, buf, strlen(buf)) < 0)
      return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  return (ISUCCESS);
}

static void	change_repertory(char *buf, char *tmp, int *lvl)
{
  char		*tok;
  int		i;

  tok = strtok(buf, "/");
  while (tok)
    {
      if (!strcmp(tok, ".."))
	{
	  lvl--;
	  i = strlen(tmp);
	  while (--i > 0 && tmp[i])
	    if (tmp[i] == '/')
	      {
		memset(&tmp[i], 0, PATH_SIZE - i);
		i = 0;
	      }
	}
      else if (strlen(tmp) + strlen(tok) + 1 < PATH_SIZE)
	{
	  strcat(tmp, "/");
	  strcat(tmp, tok);
	  lvl++;
	}
      tok = strtok(NULL, "/");
    }
}

static int	get_repertory(t_handle *handle, char *path)
{
  char		*buf;
  char		tmp[PATH_SIZE];
  int		lvl;
  int		ret;

  if (!(buf = strdup(path)))
    return (_error("Can't allocate memory : %m\n", -1));
  memcpy(tmp, handle->path, PATH_SIZE);
  lvl = handle->path_lvl;
  change_repertory(buf, tmp, &lvl);
  if (lvl >= 1 && opendir(tmp))
    {
      memcpy(handle->path, tmp, PATH_SIZE);
      handle->path_lvl = lvl;
      ret = ISUCCESS;
    }
  else
    ret = IWARNING;
  free(buf);
  return (ret);
}

int		cmd_cd(void *info, t_msg *msg)
{
  t_handle	*handle;
  char		buf[BUF_SIZE];

  handle = (t_handle*)info;
  memset(buf, 0, BUF_SIZE);
  add_log("Client %d execute command cd %s\n", 0, handle->cli_num, msg->arg);
  if (!get_repertory(handle, msg->arg))
    {
      sprintf(buf, "%s\n", handle->path);
      if (write(handle->cli_fd, buf, strlen(buf)) < 0)
	return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
    }
  else
    if (write(handle->cli_fd, "Bad repertory\n", 14) < 0)
      return (_error("Can't write on client %d: %m\n", -1, handle->cli_num));
  return (ISUCCESS);
}
