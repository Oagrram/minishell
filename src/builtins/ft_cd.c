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

void		ft_chang_value(t_env **head, char *value, char *parm)
{
	t_env *p;

	p = *head;
	while (p && p->next)
	{
		if (!(ft_strcmp(p->name, "PWD")))
		{
			ft_strdel(&(p->value));
			p->value = ft_strdup(value);
		}
		if (!(ft_strcmp(p->name, "OLDPWD")))
		{
			ft_strdel(&(p->value));
			p->value = parm;
		}
		p = p->next;
	}
}

void		ft_cd_dir(t_env **head, char *parm)
{
	char cwd[PATH_MAX];
	char *oldpwd;

	oldpwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (ft_check_acses(parm))
	{
		ft_strdel(&oldpwd);
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	ft_chang_value(head, cwd, oldpwd);
}

void		ft_cd_old_pwd(t_env **head)
{
	char	*oldpwd;

	oldpwd = NULL;
	if ((oldpwd = ft_srch_in_list(*head, "OLDPWD")) == NULL)
	{
		ft_putendl("OLDPWD: Undefined variable.");
		return ;
	}
	ft_cd_dir(head, oldpwd);
	ft_strdel(&oldpwd);
}

void		ft_cd_home(t_env **head)
{
	char	*path;
	t_env	*p;

	p = *head;
	if (!(path = ft_srch_in_list(*head, "HOME")))
	{
		ft_putendl("cd: No home directory.");
		return ;
	}
	ft_cd_dir(head, path);
	ft_strdel(&path);
}

int			ft_cd(t_env **head, char **line)
{
	if (!line[1])
		ft_cd_home(head);
	else if (line[1] && !ft_strcmp(line[1], "-"))
		ft_cd_old_pwd(head);
	else
		ft_cd_dir(head, line[1]);
	return (0);
}
