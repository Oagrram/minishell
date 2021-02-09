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

int			ft_join_dollar(char *str, int i, t_env *env, char **dollar)
{
	int		index;
	char	*srch;
	char	*ret;
	char	*tmp;

	index = 0;
	srch = NULL;
	index = ft_index(str, i + 1, '$');
	srch = ft_strsub(str, i + 1, index - i);
	ret = srch;
	if ((srch = ft_srch_in_list(env, srch)) != NULL
	&& (ft_strcmp(srch, "empty")))
	{
		if (*dollar)
		{
			tmp = *dollar;
			*dollar = ft_strjoin(*dollar, srch);
			ft_strdel(&tmp);
		}
		else
			*dollar = ft_strdup(srch);
	}
	ft_strdel(&ret);
	ft_strdel(&srch);
	return (index);
}

int			ft_dollar(char *str, char **dollar, t_env *env, int i)
{
	int		index;
	char	*tmp;
	char	*sub;

	while (str[++i])
	{
		if (str[i] == '$')
			i = ft_join_dollar(str, i, env, dollar);
		else
		{
			index = ft_index(str, i, 'c');
			if (*dollar)
			{
				tmp = *dollar;
				*dollar = ft_strjoin(*dollar,
				(sub = ft_strsub(str, i, (index - i) + 1)));
				ft_strdel(&tmp);
				ft_strdel(&sub);
			}
			else
				*dollar = ft_strsub(str, i, (index - i) + 1);
			i = index;
		}
	}
	return (1);
}

int			ft_telda(char *parmlist, char **telda, t_env *env, int i)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = NULL;
	if ((ret = ft_srch_in_list(env, "HOME")) != NULL && ft_strcmp(ret, "empty"))
	{
		while (parmlist[++i])
		{
			if (parmlist[i] == '$')
			{
				*telda = ft_strjoin(ret,
				(tmp = ft_strsub(parmlist, 1, i - 1)));
				break ;
			}
			else if (!parmlist[i + 1])
				*telda = ft_strjoin(ret,
				(tmp = ft_strsub(parmlist, 1, i)));
		}
		ft_strdel(&tmp);
	}
	ft_strdel(&ret);
	return (i - 1);
}

int			ft_check_expans(char **parmlist, t_env *env)
{
	int		i;
	char	*telda;
	char	*dollar;
	int		index;

	i = 0;
	index = -1	;
	telda = NULL;
	dollar = NULL;
	while (parmlist[++i])
	{
		if (parmlist[i][0] == '~' && (parmlist[i][1] == '/' || !parmlist[i][1]))
			index = ft_telda(parmlist[i], &telda, env, -1);
		ft_dollar(parmlist[i], &dollar, env, index);
		ft_join_dt(&telda, &dollar, &parmlist[i]);
		index = -1;
	}
	return (1);
}
