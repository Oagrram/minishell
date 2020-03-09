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

#include "minishell.h"

int			srch_in_list(t_env *p, char *found)
{
	while (p)
	{
		if (!(ft_strcmp(p->name, found)) && p->value)
			return (0);
		p = p->next;
	}
	return (1);
}

int			ft_chdir_acses(char *path)
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
	else
		return (0);
	return (0);
}

void		ft_cd_old_pwd(t_env *head)
{
	t_env	*p;
	char	*oldpwd;
	char	*pwd;

	p = head;
	oldpwd = NULL;
	pwd = NULL;
	if (srch_in_list(p, "OLDPWD"))
	{
		ft_putendl("OLDPWD: Undefined variable.");
		return ;
	}
	while (p)
	{
		if (!(ft_strcmp(p->name, "OLDPWD")))
		{
			oldpwd = ft_strdup(p->value);
		}
		if (!(ft_strcmp(p->name, "PWD")))
			pwd = ft_strdup(p->value);
		p = p->next;
	}
	p = head;
	while (p)
	{
		if (!(ft_strcmp(p->name, "PWD")))
		{
			ft_memdel((void**)&(p->value));
			p->value = oldpwd;
		}
		if (!(ft_strcmp(p->name, "OLDPWD")))
		{
			ft_memdel((void**)&(p->value));
			p->value = pwd;
		}
		p = p->next;
	}
}

void		ft_cd_previous(t_env *p)
{
	int		i;
	int		j;
	char	*path;

	i = -1;
	j = 0;
	if (srch_in_list(p, "PWD"))
	{
		ft_putendl("PWD: Undefined variable.");
		return ;
	}
	while (p)
	{
		if (!(ft_strcmp(p->name, "PWD")))
		{
			while (p->value[++i])
				if (p->value[i] == '/')
					j = i;
			if (j == 0)
				path = ft_strdup("/");
			else
				path = ft_strsub(p->value, 0, j);
			if (ft_chdir_acses(path))
			{
				ft_strdel(&(path));
				return ;
			}
			ft_strdel(&(p->value));
			p->value = path;
		}
		p = p->next;
	}
}

void		ft_cd_home(t_env *p)
{
	char	*path;
	t_env	*head;

	head = p;
	path = NULL;
	while (p)
	{
		if (!(ft_strcmp(p->name, "HOME")))
			path = p->value;
		p = p->next;
	}
	if (!path)
	{
		ft_putendl("HOME: Undefined variable.");
		return ;
	}
	p = head;
	if (ft_chdir_acses(path))
		return ;
	while (p)
	{
		if (!(ft_strcmp(p->name, "PWD")) && path)
			p->value = path;
		p = p->next;
	}
}

int			ft_cd(t_env *head, char **line)
{
	if (!line[1])
		ft_cd_home(head);
	else if (line[1] && !ft_strcmp(line[1], "-"))
		ft_cd_old_pwd(head);
	else if (line[1] && !(ft_strcmp(line[1], "../")))
		ft_cd_previous(head);
	return (0);
}
