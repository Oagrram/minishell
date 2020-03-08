/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:42:19 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/14 20:42:24 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*c;

	s = (unsigned char *)s1;
	c = (unsigned char *)s2;
	i = 0;
	while ((s[i] != '\0' || c[i] != '\0') && i < n)
	{
		if (s[i] != c[i])
			return (s[i] - c[i]);
		i++;
	}
	return (0);
}
