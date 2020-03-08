/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 21:23:36 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/16 19:01:41 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s1_2;

	if (!s1 || !s2)
		return (NULL);
	j = 0;
	i = ft_strlen((char *)s1);
	while (s2[j++] != '\0')
		i++;
	if (!(s1_2 = (char *)malloc(i + 1)))
		return (NULL);
	s1_2 = ft_strcpy(s1_2, s1);
	s1_2 = ft_strcat(s1_2, s2);
	return (s1_2);
}
