/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 21:24:29 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/18 12:46:54 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_countwords(char const *str, char c)
{
	int counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			counter++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (counter);
}

static int		ft_word_len(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**sp;

	if (!s || !(sp = (char **)malloc(sizeof(char*) *
		(ft_countwords(s, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_countwords(s, c))
	{
		k = 0;
		if (!(sp[i] = ft_strnew(ft_word_len(s + j, c))))
			sp[i] = NULL;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			sp[i][k++] = s[j++];
		sp[i][k] = '\0';
		i++;
	}
	sp[i] = 0;
	return (sp);
}
