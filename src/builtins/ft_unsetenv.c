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

#include  "../../includes/minishell.h"


t_env		*ft_remove_list(t_env **head, char *unset)
{
	t_env	*p;
	t_env	*prev;

	p = *head;
	prev = NULL;
	while (p->next)
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
	return (*head);
}

t_env		*ft_unsetenv(t_env **head, char **line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (ft_srch_in_list(*head, line[i]) != NULL)
			*head = ft_remove_list(head, line[i]);
	}
	return (*head);
}
