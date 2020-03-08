/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:24:53 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/14 20:24:59 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t t;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	while (dst[j] != '\0')
		j++;
	t = i + j;
	if (j > size)
		return (i + size);
	while (*src && j < size - 1)
		dst[j++] = *src++;
	dst[j] = '\0';
	return (t);
}
