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

int			ft_chdir(char *path)
{
	struct stat *statbuf;

	statbuf = NULL;
	if (chdir(path) == -1)
	{
		if (stat(path, statbuf) == -1)
		{
			printf("error\n");
			return (1);
		}
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
	while (p)
	{
		if (!(ft_strcmp(p->name, "OLDPWD")))
		{
			oldpwd = ft_strdup(p->value);
			if (ft_chdir(oldpwd) == 1)
			{
				ft_memdel((void **)oldpwd);
				return ;
			}
		}
		if (!(ft_strcmp(p->name, "PWD")))
			pwd = ft_strdup(p->value);
		p = p->next;
	}
	if (!oldpwd)
	{
		printf (": No such file or directory.\n");
		return;
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
	int 	i;
	int 	j;
	char 	*path;

	i = -1;
	j = 0;
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
			//ft_memdel((void **)p->value);
			p->value = path;
			// if (ft_chdir(oldpwd) == 1)
			// {
			// 	ft_memdel((void **)oldpwd);
			// 	return ;
			// }
		}
		p = p->next;
	}
	 chdir(p->value);
}

int			ft_cd(t_env *head, char **line)
{
	char	*path;
	t_env	*p;

	p = head;
	if (!line[1])
	{
		while (p->next)
		{
			if (!(ft_strcmp(p->name, "HOME")))
				path = p->value;
			p = p->next;
		}
		p = head;
		while (p)
		{
			if (!(ft_strcmp(p->name, "PWD")) && path)
				p->value = path;
			p = p->next;
		}
	}
	else if (line[1] && !ft_strcmp(line[1], "-"))
		ft_cd_old_pwd(head);
	else if (line[1] && !(ft_strcmp(line[1], "../")))
		ft_cd_previous(head);
	return (0);
}
