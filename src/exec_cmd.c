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

char		*ft_check_prog(t_env *head, char *command)
{
	int		i;
	char	*path;
	char	**split;

	split = NULL;
	path = NULL;
	i = -1;
	if (command[0] == '.' || command[0] == '/')
	{
		if (access(command, F_OK))
		{
			ft_putendl("Command not found.");
			return (NULL);
		}
		return (command);
	}
	path = ft_srch_in_list(head, "PATH");
	if (path == NULL || !ft_strcmp(path, "empty"))
	{
		ft_putendl("Command not found.");
		return (NULL);
	}
	if (!(split = ft_strsplit(path, ':')))
		exit(1);
	while (split[++i])
	{
		path = ft_add_slach(split[i], command);
		if (!(access(path, F_OK)))
			break ;
		ft_strdel(&path);
	}
	ft_bonus_freedoubledem(split);
	if (path == NULL)
		ft_putendl("Command not found.");
	return (path);
}
