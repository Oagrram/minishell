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

void		fill_new_node(t_env *p, t_env **head, char **line)
{
	if (p != NULL)
	{
		while ((p)->next)
			p = (p)->next;
		(p)->next = ft_memalloc(sizeof(t_env));
		p = (p)->next;
	}
	else
	{
		*head = ft_memalloc(sizeof(t_env));
		p = *head;
	}
	(p)->name = ft_strdup(line[1]);
	if (line[2])
		(p)->value = ft_strdup(line[2]);
	else
		(p)->value = NULL;
	(p)->next = NULL;
}

void		ft_setenv(t_env **head, char **line)
{
	char	*ret;
	t_env	*p;

	ret = NULL;
	p = *head;
	if (!setenv_check(line))
		return ;
	if ((ret = ft_srch_in_list(*head, line[1])) == NULL)
	{
		fill_new_node(p, head, line);
	}
	else
	{
		ft_strdel(&ret);
		add_val_list(*head, line);
	}
}
