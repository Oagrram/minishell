/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:21:31 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/14 20:21:35 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s1;
	size_t				i;

	i = 0;
	s1 = s;
	while (0 < n)
	{
		if (s1[i] == (unsigned char)c)
			return ((char *)s1 + i);
		i++;
		n--;
	}
	return (NULL);
}
