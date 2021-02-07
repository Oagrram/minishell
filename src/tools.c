/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:47:40 by oagrram           #+#    #+#             */
/*   Updated: 2020/03/06 11:47:42 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_index(char *str, int index, char srch)
{
	if (srch == '$')
	{
		while (str[index] && str[index] == '$')
		{
			index++;
		}
		while (str[index] && ft_isalnum(str[index]) && ft_isalpha(str[index]))
		{
			index++;
		}
		return (index - 1);
	}
	else
	{
		while (str[index] && str[index] != '$')
		{
			index++;
		}
		return (index - 1);
	}
	return (0);
}

char		*ft_add_slach(char *path, char *comand)
{
	char	*new;
	char	*tmp;

	tmp = NULL;
	new = NULL;
	tmp = ft_strjoin(path, "/");
	new = ft_strjoin(tmp, comand);
	ft_strdel(&(tmp));
	return (new);
}

char		*ft_srch_in_list(t_env *p, char *found)
{
	if (found[0] == '~')
	{
		found = "HOME";
	}
	if (found[0] == '$')
		found = &found[1];
	while (p)
	{
		if (!(ft_strcmp(p->name, found)))
		{
			if (p->value)
				return (ft_strdup(p->value));
			else
				return ("empty");
		}
		p = p->next;
	}
	return (NULL);
}

int			ft_check_acses(char *path)
{
	if (access(path, F_OK))
	{
		ft_putendl("Does not exist");
		return (1);
	}
	else if (chdir(path) == -1)
	{
		ft_putstr(path);
		ft_putendl(": Permission denied.");
		return (1);
	}
	return (0);
}
