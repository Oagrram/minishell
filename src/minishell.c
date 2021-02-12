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

int			check_file(char *path, char **table)
{
	if (access(path, X_OK))
		ft_putendl("Permission Denied.");
	else
		ft_putendl("Command not found.");
	ft_bonus_freedoubledem(table);
	return (0);
}

char		**lst_to_tabel(t_env *head, int nbr)
{
	char	**table;
	t_env	*p;
	char	*tmp;

	p = head;
	tmp = NULL;
	if (!head)
		return (NULL);
	while (p && ++nbr)
		p = p->next;
	table = (char **)malloc(sizeof(char *) * (nbr + 1));
	nbr = -1;
	while (head)
	{
		if (head->value)
			table[++nbr] = ft_strjoin(
			(tmp = ft_strjoin(head->name, "=")), head->value);
		else
			table[++nbr] = ft_strjoin(head->name, "=");
		ft_strdel(&tmp);
		head = head->next;
	}
	table[++nbr] = NULL;
	return (table);
}

void		ft_read_line(char *enter, t_env **head, char *path)
{
	char	**parmlist;
	pid_t	pid;
	char	**table;

	table = NULL;
	if ((parmlist = ft_strsplitstr(enter, " \t\n\r\a\"")))
	{
		if (ft_check_expans(parmlist, *head) && ft_is_builtins(parmlist[0]))
			ft_execut_builtins(parmlist, head);
		else if ((path = ft_check_prog(*head, parmlist[0])))
		{
			pid = fork();
			if (pid != 0)
				wait(NULL);
			if (pid == 0 && (execve(path, parmlist,
			(table = lst_to_tabel(*head, 0))) == -1))
			{
				check_file(path, table);
				exit(0);
			}
			ft_bonus_freedoubledem(table);
		}
		ft_strdel(&path);
		ft_bonus_freedoubledem(parmlist);
	}
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
	char	*path;

	path = NULL;
	head = NULL;
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
				ft_read_line(line, &head, path);
			ft_strdel(&line);
			ft_putstr("$> ");
		}
	}
	return (ac);
}
