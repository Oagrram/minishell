/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 21:20:39 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/14 21:20:42 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned long i;
	unsigned char *s;

	i = 0;
	if (!(s = (unsigned char *)malloc(size * sizeof(unsigned char))))
		return (NULL);
	while (i < size)
		s[i++] = 0;
	return (s);
}
