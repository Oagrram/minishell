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

char		*ft_srch_in_list(t_env *p, char *found)
{
	if (found[0] == '~')
	{
		found = "HOME";
	}
	if (found[0] == '$')
		found = &found[1];
	while (p->next)
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

