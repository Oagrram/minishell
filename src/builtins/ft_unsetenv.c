/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:25:17 by oagrram           #+#    #+#             */
/*   Updated: 2021/01/29 15:25:17 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_remove_list(t_env **head, char *unset)
{
	t_env	*p;
	t_env	*prev;

	p = *head;
	prev = NULL;
	while (p)
	{
		if (!ft_strcmp(p->name, unset))
		{
			if (prev)
				prev->next = p->next;
			else
				*head = p->next;
			ft_strdel(&(p->name));
			ft_strdel(&(p->value));
			break ;
		}
		prev = p;
		p = p->next;
	}
}

t_env		*ft_unsetenv(t_env **head, char **line)
{
	int		i;
	char	*ret;

	i = -1;
	ret = NULL;
	while (line[++i])
	{
		if ((ret = ft_srch_in_list(*head, line[i])) != NULL)
			ft_remove_list(head, line[i]);
		ft_strdel(&ret);
	}
	return (*head);
}
