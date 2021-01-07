/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:35:19 by oagrram           #+#    #+#             */
/*   Updated: 2020/03/04 15:35:21 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			setenv_check(char **line)
{
	int		i;

	i = -1;
	if (!ft_isalpha(line[1][0]) && line[1][0] != '_')
	{
		ft_putendl("setenv: Variable name must begin with a letter.");
		return (0);
	}
	while (line[1][++i])
	{
		if (!ft_isalnum(line[1][i]) && line[1][i] != '_')
		{
			ft_putendl("setenv: Name must contain alphanumeric characters.");
			return (0);
		}
	}
	return (1);
}

void		add_val_list(t_env *p, char **line)
{
	while (p)
	{
		if (!ft_strcmp(p->name, line[1]))
		{
			if (line[2])
			{
				ft_strdel(&(p->value));
				p->value = ft_strdup(line[2]);
			}
			else
			{
				ft_strdel(&(p->value));
			}
			return ;
		}
		p = p->next;
	}
}

void		ft_setenv(t_env *p, char **line)
{
	char	*ret;

	if (!setenv_check(line))
		return ;
	ret = ft_srch_in_list(p, line[1]);
	if (ret == NULL)
	{
		while (p->next)
			p = p->next;
		if ((p->next = ft_memalloc(sizeof(t_env))) == NULL)
			exit(1);
		if ((p->name = ft_strdup(line[1])) == NULL)
			exit(1);
		p->name = ft_strdup(line[1]);
		if (line[2])
		{
			if ((p->value = ft_strdup(line[2])) == NULL)
				exit(1);
		}
		else
			p->value = NULL;
	}
	else
	{
		add_val_list(p, line);
	}
}

int			check_line(char **line, int max, char *cammnd)
{
	int		i;

	i = -1;
	while (line[++i])
		;
	if (!ft_strcmp(cammnd, "unsetenv"))
	{
		if (!line[1])
		{
			ft_putendl("unsetenv : Too few arguments.");
			return (0);
		}
		return (1);
	}
	else
	{
		if (i > max)
		{
			ft_putstr(cammnd);
			ft_putendl(" : Too many arguments.");
			return (0);
		}
	}
	return (1);
}

int			ft_echo(char **line)
{
	int		i;

	i = 0;
	while (line[++i])
	{
		ft_putstr(line[i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}

int			ft_env(t_env *head)
{
	while (head->next)
	{
		ft_putstr(head->name);
		ft_putchar('=');
		if (!head->value)
			ft_putendl("");
		else
			ft_putendl(head->value);
		head = head->next;
	}
	return (0);
}

t_env		*ft_remove_list(t_env **head, char *unset)
{
	t_env	*p;
	t_env	*prev;

	p = *head;
	prev = NULL;
	while (p->next)
	{
		if (!ft_strcmp(p->name, unset))
		{
			if (prev)
				prev->next = p->next;
			else
				*head = p->next;
			ft_strdel(&(p->name));
			ft_strdel(&(p->value));
			break ;
		}
		prev = p;
		p = p->next;
	}
	return (*head);
}

t_env		*ft_unsetenv(t_env **head, char **line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (ft_srch_in_list(*head, line[i]) != NULL)
			*head = ft_remove_list(head, line[i]);
	}
	return (*head);
}

int			ft_execut_builtins(char **line, t_env **head)
{
	if (!ft_strcmp(line[0], "echo"))
		ft_echo(line);
	if (!ft_strcmp(line[0], "cd") && check_line(line, 2, "cd"))
		ft_cd(head, line);
	if (!ft_strcmp(line[0], "env") && check_line(line, 1, "env"))
		ft_env(*head);
	if (!ft_strcmp(line[0], "setenv") && check_line(line, 3, "setenv"))
	{
		if (!line[1])
			ft_env(*head);
		else
			ft_setenv(*head, line);
	}
	if (!ft_strcmp(line[0], "unsetenv") && check_line(line, 1, "unsetenv"))
		*head = ft_unsetenv(head, line);
	return (0);
}

int			ft_is_builtins(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd") ||
	!ft_strcmp(command, "setenv") || !ft_strcmp(command, "unsetenv")
	|| !ft_strcmp(command, "exit") || !ft_strcmp(command, "env"))
		return (1);
	else
		return (0);
}

char		*ft_add_slach(char *path, char *comand)
{
	char	*new;
	char	*tmp;

	if ((tmp = ft_strjoin(path, "/")) == NULL)
		exit(1);
	if ((new = ft_strjoin(tmp, comand)) == NULL)
		exit(1);
	ft_strdel(&(tmp));
	return (new);
}

char		*ft_chek_prog(t_env *head, char *comand)
{
	char	**split;
	int		i;
	char	*newpath;
	char	*envpath;
	struct stat state;

	i = -1;
	envpath = ft_srch_in_list(head, "PATH");
	if ((envpath == NULL) || (!ft_strcmp(envpath, "empty")))
	{
		ft_putendl("Cammand not found.");
		return (NULL);
	}
	if (!(split = ft_strsplit(envpath, ':')))
		exit(1);
	while (split[++i])
	{
		newpath = ft_add_slach(split[i], comand);
		if (!stat(newpath, &state))
		{
			if (S_ISDIR(state.st_mode))
			{
				ft_putendl("is diractory.");
				ft_strdel(&newpath);
			}
			else if ((access(newpath, X_OK)))
			{
				ft_putendl("Permission denied.");
				ft_strdel(&newpath);
			}
			ft_bonus_freedoubledem(split);
			return (newpath);
		}
		ft_strdel(&newpath);
	}
	ft_putendl("Command not found.");
	ft_bonus_freedoubledem(split);
	return (NULL);
}

int		ft_check_expans(char **parmlist, t_env *env)
{
	int i;
	char *ret;

	i = 0;
	while (parmlist[++i])
	{
		if (parmlist[i][0] == '$' || parmlist[i][0] == '~')
		{
			if ((ret = ft_srch_in_list(env, &(parmlist[i][0]))) != NULL &&
			(ft_strcmp(ret, "empty")))
			{
				if (parmlist[i][0] == '~' && parmlist[i][1])
				{
					ret = ft_strjoin(ret, &parmlist[i][1]);
					ft_strdel(&parmlist[i]);
					parmlist[i] = ret;
				}
				else
				{
					ft_strdel(&parmlist[i]);
					parmlist[i] = ft_strdup(ret);
				}
			}
			else
			{
				ft_putstr(&parmlist[i][1]);
				ft_putendl(": Undefined variable.");
				return (0);
			}
		}
	}
	return (1);
}

int			ft_read_line(char *enter, t_env **head, char **env)
{
	char	**parmlist;
	char	*path;
	pid_t	pid;

	if ((parmlist = ft_strsplit(enter, ' ')))
	{
		printf("i am not heresr\n");
		if (ft_is_builtins(parmlist[0]))
		{
			if (ft_check_expans(parmlist, *head) == 0)
			{
				return(0);
			}
			ft_execut_builtins(parmlist, head);
		}
		else if ((path = ft_chek_prog(*head, parmlist[0])))
		{
			pid = fork();
			if (pid != 0)
				wait(NULL);
			if (pid == 0)
			{
				if (execve(path, parmlist, env) == -1)
				{
					printf("ERROR\n");
				}
				ft_strdel(&path);
			}
		}
		// ft_strdel(&path);
		ft_bonus_freedoubledem(parmlist);
	}
	return (0);
}

t_env		*ft_swith_data(char **env, int j)
{
	t_env	*head;
	t_env	*p;
	char	**envline;

	if ((p = ft_memalloc(sizeof(t_env))) == NULL)
		exit(1);
	head = p;
	while (env[++j])
	{
		envline = ft_strsplit(env[j], '=');
		if ((p->name = ft_strdup(envline[0])) == NULL)
			exit(1);
		if (envline[1])
		{
			if ((p->value = ft_strdup(envline[1])) == NULL)
				exit(1);
		}
		else
			p->value = NULL;
		if (env[j + 1])
			if ((p->next = ft_memalloc(sizeof(t_env))) == NULL)
				exit(1);
		p = p->next;
		ft_bonus_freedoubledem(envline);
	}
	return (head);
}

void		free_env(t_env **head)
{
	t_env *tmp;

	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->value);
		ft_memdel((void**)&(tmp));
	}
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*head;

	av[0][0] = (char)ac;
	head = ft_swith_data(env, -1);
	ft_putstr("$> ");
	while (1)
	{
		while (get_next_line(0, &line))
		{
			if (!ft_strcmp(line, "exit"))
			{
				free_env(&(head));
				exit(1);
			}
			if (strlen(line))
			{
				ft_read_line(line, &head, env);
			}
			ft_strdel(&line);
			ft_putstr("$> ");
		}
	}
	return (ac);
}
