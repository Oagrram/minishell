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

char		*ft_check_access(char **split, char *command)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (split[++i])
	{
		path = ft_add_slach(split[i], command);
		if (!(access(path, F_OK)))
			break ;
		ft_strdel(&path);
	}
	ft_bonus_freedoubledem(split);
	return (path);
}

char		*ft_check_prog(t_env *head, char *command)
{
	char	*path;
	char	**split;

	split = NULL;
	path = NULL;
	if ((command[0] == '.' || command[0] == '/') && !access(command, F_OK))
		return (ft_strdup(command));
	if (((command[0] == '.' || command[0] == '/') && access(command, F_OK)) ||
	(!(path = ft_srch_in_list(head, "PATH")) || !ft_strcmp(path, "empty")))
	{
		ft_strdel(&path);
		ft_putendl("Command not found.");
		return (NULL);
	}
	split = ft_strsplit(path, ':');
	ft_strdel(&path);
	path = ft_check_access(split, command);
	if (path == NULL)
		ft_putendl("Command not found.");
	return (path);
}
