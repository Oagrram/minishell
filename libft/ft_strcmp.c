/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:42:04 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/14 20:42:06 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*s;
	unsigned char	*c;

	c = (unsigned char*)s2;
	s = (unsigned char *)s1;
	i = 0;
	while (s[i] != '\0' || c[i] != '\0')
	{
		if (s[i] != c[i])
			return (s[i] - c[i]);
		i++;
	}
	return (0);
}
