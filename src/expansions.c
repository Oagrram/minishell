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

int		ft_index(char *str, int index,char srch)
{
	if (srch == '$')
	{
		while(str[index] &&  str[index] == '$')
		{
			index++;
		}
		while (str[index] && ft_isalnum(str[index]) && ft_isalpha(str[index]))
		{
			index++;
		}
		return (index - 1);
	}
	else
	{
		while (str[index] && str[index] != '$')
		{
			index++;
		}
		return (index - 1);
	}
	return (0);
}

int		ft_dollar(char *str, char **dollar, t_env *env, int i)
{
	char	*srch;
	int		index;

	index = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			index = ft_index(str, i + 1, '$');
			srch = ft_strsub(str, i + 1, index - i);
			printf("stop there %d\n and susb from %d \n",index,index - i);
			if ((srch = ft_srch_in_list(env, srch)) != NULL
			&& (ft_strcmp(srch, "empty")))
			{
				if (*dollar)
					*dollar = ft_strjoin(*dollar, srch);
				else
					*dollar = ft_strdup(srch);
			}
			i = index;
			ft_strdel(&srch);
		}
		else 
		{
			index = ft_index(str, i, 'c');
			printf ("sub == %s\n",ft_strsub(str, i, (index - i)));
			printf ("<<<<<<<<<<< index === %d ||| i == %d>>>>>>>>>>>>\n",ft_index(str,i,'c'), i);
			if (*dollar)
			{
				*dollar = ft_strjoin(*dollar, ft_strsub(str, i, (index - i) + 1));
			}
			else
				*dollar = ft_strdup(ft_strsub(str, i, (index - i) + 1));
			i = index;
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
		ft_dollar(parmlist[i], &dollar, env,
		((parmlist[i][0] == '~' && parmlist[i][1] == '/') ? 1 : -1));
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

