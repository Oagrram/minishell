/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:47:14 by oagrram           #+#    #+#             */
/*   Updated: 2021/01/29 15:47:15 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_index(char *str, int index)
{
	while(str[index] == '$')
	{
		index++;
	}
	while (str[index] && ft_isalnum(str[index]) && ft_isalpha(str[index]))
	{
		index++;
	}
	return (index - 1);
}

int		ft_dollar(char *str, char **dollar, t_env *env)
{
	int		i;
	char	*srch;
	int		index;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			index = ft_index(str, i + 1);
			srch = ft_strsub(str, i + 1, index - i);
			if ((srch = ft_srch_in_list(env, srch)) != NULL
			&& (ft_strcmp(srch, "empty")))
			{
				if (*dollar)
					*dollar = ft_strjoin(*dollar, srch);
				else
					*dollar = ft_strdup(srch);
			}
			ft_strdel(&srch);
		}
	}
	return (1);
}

int		ft_telda(char *parmlist,  char **telda, t_env *env)
{
	int i;

	i = 0;
	if ((*telda = ft_srch_in_list(env, "HOME")) != NULL
	&& (ft_strcmp(*telda, "empty")))
	{
		while (parmlist[++i])
		{
			if (parmlist[i] == '$')
			{
				*telda = ft_strjoin(*telda, ft_strsub(parmlist, 1, i - 1));
				break ;
			}
			else if (!parmlist[i + 1])
			{
				*telda = ft_strjoin(*telda, ft_strsub(parmlist, 1, i));
			}
		}
	}
	return (1);
}

int		ft_check_expans(char **parmlist, t_env *env)
{
	int i;
	char *telda;
	char *dollar;

	i = 0;
	telda = NULL;
	dollar = NULL;
	while (parmlist[++i])
	{
		if (parmlist[i][0] == '~' && (parmlist[i][1] == '/' || !parmlist[i][1]))
		{
			ft_telda(parmlist[i], &telda, env);
		}
		ft_dollar(parmlist[i], &dollar, env);
		if (telda && dollar)
		{
			ft_strdel(&parmlist[i]);
			parmlist[i] = ft_strjoin(telda, dollar);
		}
		else if (telda || dollar)
		{
			ft_strdel(&parmlist[i]);
			parmlist[i] = ft_strdup(((telda) ? telda : dollar));
		}
		ft_strdel(&dollar);
		ft_strdel(&telda);
	}
	return (1);
}

