/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:25:11 by oagrram           #+#    #+#             */
/*   Updated: 2021/01/29 15:25:12 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		add_val_list(t_env *p, char **line)
{
	while (p)
	{
		if (!ft_strcmp(p->name, line[1]))
		{
			if (line[2])
			{
				ft_strdel(&(p->value));
				p->value = ft_strdup(line[2]);
			}
			else
			{
				ft_strdel(&(p->value));
			}
			return ;
		}
		p = p->next;
	}
}

int			setenv_check(char **line)
{
	int		i;

	i = -1;
	if (!ft_isalpha(line[1][0]) && line[1][0] != '_')
	{
		ft_putendl("setenv: Variable name must begin with a letter.");
		return (0);
	}
	while (line[1][++i])
	{
		if (!ft_isalnum(line[1][i]) && line[1][i] != '_')
		{
			ft_putendl("setenv: Name must contain alphanumeric characters.");
			return (0);
		}
	}
	return (1);
}

void		ft_setenv(t_env *p, char **line)
{
	char	*ret;

	ret = NULL;
	if (!setenv_check(line))
		return ;
	if ((ret = ft_srch_in_list(p, line[1])) == NULL)
	{
		while (p->next)
			p = p->next;
		p->next = ft_memalloc(sizeof(t_env));
		p = p->next;
		p->name = ft_strdup(line[1]);
		if (line[2])
			p->value = ft_strdup(line[2]);
		else
			p->value = NULL;
	}
	else
	{
		add_val_list(p, line);
	}
}
