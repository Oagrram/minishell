/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <midoxthex@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:22:38 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/19 19:22:21 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s;

	i = ft_strlen(s1);
	if (!(s = ft_strnew(i)))
		return (NULL);
	i = 0;
	ft_strcpy(s, s1);
	return (s);
}
