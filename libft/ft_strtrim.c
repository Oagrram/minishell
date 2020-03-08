/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 21:24:12 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/14 21:24:14 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		i;
	char	*c;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen((char *)s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
	{
		if (!(c = (char *)malloc(1)))
			return (NULL);
		c[0] = '\0';
		return (c);
	}
	while (s[j - 1] == ' ' || s[j - 1] == '\n' || s[j - 1] == '\t')
		j--;
	if (!(c = ft_strsub(s, i, j - i)))
		return (NULL);
	return (c);
}
