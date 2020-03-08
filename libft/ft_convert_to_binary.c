/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_to_binary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 21:52:43 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/18 12:22:24 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_convert_to_binary(int n)
{
	int		tab[60];
	char	*tab2;
	int		i;
	int		j;

	i = 0;
	while (n)
	{
		tab[i++] = n % 2;
		n /= 2;
	}
	tab2 = (char*)malloc(i + 1);
	j = 0;
	i--;
	while (i >= 0)
		tab2[i--] = tab[j++] + '0';
	tab2[j] = '\0';
	return (tab2);
}
