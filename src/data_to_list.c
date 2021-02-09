/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:51:34 by oagrram           #+#    #+#             */
/*   Updated: 2021/01/29 15:51:35 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env		*ft_swith_data(char **env, int j)
{
	char	**envline;
	t_env	*head;
	t_env	*p;

	if (!env[0])
		return (NULL);
	p = ft_memalloc(sizeof(t_env));
	head = p;
	while (env[++j])
	{
		envline = ft_strsplit(env[j], '=');
		p->name = ft_strdup(envline[0]);
		if (envline[1])
			p->value = ft_strdup(envline[1]);
		else
			p->value = NULL;
		if (env[j + 1])
			p->next = ft_memalloc(sizeof(t_env));
		else
			p->next = NULL;
		p = p->next;
		ft_bonus_freedoubledem(envline);
	}
	return (head);
}
