/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:19:47 by oagrram           #+#    #+#             */
/*   Updated: 2021/01/29 15:19:49 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
