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

int		ft_echo(char **line)
{
	int i;

	i = 0;
	while (line[++i])
	{
		ft_putstr(line[i]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}

int		ft_env(t_env *head)
{
	while (head != NULL)
	{
		ft_putstr(head->name);
		ft_putchar('=');
		ft_putendl(head->value);
		head = head->next;
	}
	return (0);
}

int		execut_builtins(char **line, t_env *head)
{
	if (!ft_strcmp(line[0], "echo"))
		ft_echo(line);
	if (!ft_strcmp(line[0], "cd"))
		ft_cd(head, line);
	if (!ft_strcmp(line[0], "env"))
		ft_env(head);
	return (0);
}

int		is_builtins(char *command)
{
	if (!ft_strcmp(command, "echo") || !ft_strcmp(command, "cd") ||
	!ft_strcmp(command, "setenv") || !ft_strcmp(command, "unsetenv")
	|| !ft_strcmp(command, "exit") || !ft_strcmp(command, "env"))
		return (1);
	else
		return (0);
}

int		read_line(char *enter, t_env *head, char **env)
{
	char **line;

	line = ft_strsplit(enter, ' ');
	if (is_builtins(line[0]))
		execut_builtins(line, head);
	else
		execve("/bin/ls", line, env);
	ft_bonus_freedoubledem(line);
	return (0);
}

t_env	*swith_data(char **env, int j)
{
	int i;
	t_env *head;
	t_env *p;
	char **envline;

	i = -1;
	while (env[++i])
		;
	if ((p = ft_memalloc(sizeof(t_env))) == NULL)
		exit(1);
	head = p;
	while (++j < i)
	{
		envline = ft_strsplit(env[j], '=');
		if ((p->name = ft_memalloc(ft_strlen(envline[0]))) == NULL)
			exit(1);
		p->name = ft_strdup(envline[0]);
		if ((p->value = ft_memalloc(ft_strlen(envline[1]))) == NULL)
			exit(1);
		p->value = ft_strdup(envline[1]);
		if ((j + 1) != i)
			if ((p->next = ft_memalloc(sizeof(t_env))) == NULL)
				exit(1);
		p = p->next;
		ft_bonus_freedoubledem(envline);
	}
	return (head);
}

int		main(int ac, char **av, char **env)
{
	char *line;
	t_env *head;

	av[0][0] = (char)ac;
	head = swith_data(env, -1);
	// while (head != NULL)
	// {
	// 	printf("%s=%s\n",head->name, head->value);
	// 	head = head->next;
	// }
	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(line, "exit"))
			exit(1);
		if (ft_strlen(line))
		{
			read_line(line, head, env);
			free(line);
		}
	}
	return (0);
}
