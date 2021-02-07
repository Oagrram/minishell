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

int			ft_join_dollar(char *str, int i, t_env *env, char **dollar)
{
	int		index;
	char	*srch;
	char	*ret;

	index = 0;
	srch = NULL;
	index = ft_index(str, i + 1, '$');
	srch = ft_strsub(str, i + 1, index - i);
	ret = srch;
	if ((srch = ft_srch_in_list(env, srch)) != NULL
	&& (ft_strcmp(srch, "empty")))
	{
		if (*dollar)
			*dollar = ft_strjoin(*dollar, srch);
		else
			*dollar = ft_strdup(srch);
		ft_strdel(&srch);
		ft_strdel(&ret);
	}
	return (index);
}

void		ft_join_dt(char **telda, char **dollar, char **parmlist)
{
	if (*telda && *dollar)
	{
		ft_strdel(&(*parmlist));
		*parmlist = ft_strjoin(*telda, *dollar);
	}
	else if (*telda || *dollar)
	{
		ft_strdel(&(*parmlist));
		*parmlist = ft_strdup(((*telda) ? (*telda) : (*dollar)));
	}
	ft_strdel(&(*dollar));
	ft_strdel(&(*telda));
}

int			ft_dollar(char *str, char **dollar, t_env *env, int i)
{
	int		index;

	index = 0;
	printf("i am in dollar start from %d\n",i);
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i = ft_join_dollar(str, i, env, dollar);
		}
		else
		{
			index = ft_index(str, i, 'c');
			if (*dollar)
				*dollar = ft_strjoin(*dollar,
				ft_strsub(str, i, (index - i) + 1));
			else
				*dollar = ft_strsub(str, i, (index - i) + 1);
				printf("i am in dollar with %s\n",*dollar);
			i = index;
		}
	}
	return (1);
}

int			ft_telda(char *parmlist, char **telda, t_env *env)
{
	int		i;

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
	return (i - 1);
}

int			ft_check_expans(char **parmlist, t_env *env)
{
	int		i;
	char	*telda;
	char	*dollar;
	int  	index;

	i = 0;
	index = -1	;
	telda = NULL;
	dollar = NULL;
	while (parmlist[++i])
	{
		if (parmlist[i][0] == '~' && (parmlist[i][1] == '/' || !parmlist[i][1]))
		{
			index = ft_telda(parmlist[i], &telda, env);
			printf(" TELDA ==  %s \n",telda);
		}
		ft_dollar(parmlist[i], &dollar, env, index);
		ft_join_dt(&telda, &dollar, &parmlist[i]);
	}
	return (1);
}
