/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:24:30 by oagrram           #+#    #+#             */
/*   Updated: 2021/01/29 15:24:32 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void		ft_cd_old_pwd(t_env **head)
{
	t_env	*p;
	char	*oldpwd;
	char	*pwd;

	p = *head;
	oldpwd = NULL;
	pwd = NULL;
	if (ft_srch_in_list(p, "OLDPWD") == NULL)
	{
		ft_putendl("OLDPWD: Undefined variable.");
		return ;
	}
	while (p)
	{
		if (!(ft_strcmp(p->name, "OLDPWD")))
		{
			ft_cd_dir(head, p->value);
			return ;
		}
		// 	oldpwd = ft_strdup(p->value);
		// if (!(ft_strcmp(p->name, "PWD")))
		// 	pwd = ft_strdup(p->value);
		p = p->next;
	}
	// p = *head;
	// while (p)
	// {
	// 	if (!(ft_strcmp(p->name, "PWD")))
	// 	{
	// 		ft_memdel((void**)&(p->value));
	// 		p->value = oldpwd;
	// 	}
	// 	if (!(ft_strcmp(p->name, "OLDPWD")))
	// 	{
	// 		ft_memdel((void**)&(p->value));
	// 		p->value = pwd;
	// 	}
	// 	p = p->next;
	// }
}

// void		ft_cd_previous(t_env **head)
// {
// 	int		i;
// 	int		j;
// 	char	*path;
// 	t_env 	*p;

// 	p = *head;
// 	i = -1;
// 	j = 0;
// 	if (ft_srch_in_list(p, "PWD") == NULL)
// 	{
// 		ft_putendl("PWD: Undefined variable.");
// 		return ;
// 	}
// 	while (p)
// 	{
// 		if (!(ft_strcmp(p->name, "PWD")))
// 		{
// 			while (p->value[++i])
// 				if (p->value[i] == '/')
// 					j = i;
// 			if (j == 0)
// 				path = ft_strdup("/");
// 			else
// 				path = ft_strsub(p->value, 0, j);
// 			if (ft_check_acses(path))
// 			{
// 				ft_strdel(&(path));
// 				return ;
// 			}
// 			ft_strdel(&(p->value));
// 			p->value = path;
// 		}
// 		p = p->next;
// 	}
// }

void		ft_chang_value(t_env **head, char *value)
{
	t_env *p;

	p = *head;
	while (p->next)
	{
		if (!(ft_strcmp(p->name, "PWD")))
		{
			ft_strdel(&(p->value));
			p->value = ft_strdup(value);
		}
		p = p->next;
	}
}

void		ft_cd_home(t_env **head)
{
	char	*path;
	t_env	*p;

	p = *head;
	path = ft_srch_in_list(*head, "HOME");
	if (!path)
	{
		ft_putendl("cd: No home directory.");
		return ;
	}
	ft_cd_dir(head, path);
}

void		ft_cd_dir(t_env **head, char *parm)
{
	char cwd[PATH_MAX];

	if (ft_check_acses(parm))
		return ;
	getcwd(cwd, sizeof(cwd));
	ft_chang_value(head, cwd);
	//cant free cwd
}

int			ft_cd(t_env **head, char **line)
{
	if (!line[1])
		ft_cd_home(head);
	else if (line[1] && !ft_strcmp(line[1], "-"))
		ft_cd_old_pwd(head);
	// else if (line[1] && !(ft_strcmp(line[1], "../")))
	// 	ft_cd_previous(head);
	else
		ft_cd_dir(head, line[1]);
	return (0);
}

