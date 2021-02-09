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

#include "../includes/minishell.h"

int			check_file(char *path)
{
	if (access(path, X_OK))
		ft_putendl("Permission Denied.");
	else
		ft_putendl("Command not found.");
	return (0);
}

int			ft_read_line(char *enter, t_env **head, char **env)
{
	char	**parmlist;
	char	*path;
	pid_t	pid;

	path = NULL;
	if ((parmlist = ft_strsplitstr(enter, " \t\n\r\a\"")))
	{
		ft_check_expans(parmlist, *head);
		if (ft_is_builtins(parmlist[0]))
			ft_execut_builtins(parmlist, head);
		else if ((path = ft_check_prog(*head, parmlist[0])))
		{
			pid = fork();
			if (pid != 0)
				wait(NULL);
			if ((pid == 0) && (execve(path, parmlist, env) == -1))
			{
				check_file(path);
				exit(0);
			}
		}
		ft_strdel(&path);
		ft_bonus_freedoubledem(parmlist);
	}
	return (0);
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
	printf("i am out of >> swith data");
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
				ft_read_line(line, &head, env);
			ft_strdel(&line);
			ft_putstr("$> ");
		}
	}
	return (ac);
}
