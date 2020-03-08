/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:25:13 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/14 20:25:15 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	a;
	char	*v;

	i = 0;
	a = (char)c;
	v = (char *)s;
	while (v[i] != '\0')
	{
		if (v[i] == a)
			return (v + i);
		i++;
	}
	if (v[i] == a)
		return (v + i);
	return (0);
}
