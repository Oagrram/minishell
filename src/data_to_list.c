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
	t_env	*head;
	t_env	*p;
	char	**envline;

	if ((p = ft_memalloc(sizeof(t_env))) == NULL)
		exit(1);
	head = p;
	while (env[++j])
	{
		envline = ft_strsplit(env[j], '=');
		if ((p->name = ft_strdup(envline[0])) == NULL)
			exit(1);
		if (envline[1])
		{
			if ((p->value = ft_strdup(envline[1])) == NULL)
				exit(1);
		}
		else
			p->value = NULL;
		if (env[j + 1])
			if ((p->next = ft_memalloc(sizeof(t_env))) == NULL)
				exit(1);
		p = p->next;
		ft_bonus_freedoubledem(envline);
	}
	return (head);
}

