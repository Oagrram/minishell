/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:11:19 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/15 18:01:32 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_intlen(int n)
{
	int			e;

	e = 0;
	if (n == 0)
		e = 1;
	else
		while (n)
		{
			n = n / 10;
			e++;
		}
	return (e);
}

static char		*ft_positive(int n, int ilen)
{
	char		*array;

	if (!(array = (char*)malloc(sizeof(char) * ilen + 1)))
		return (NULL);
	array[ilen] = '\0';
	ilen--;
	while (ilen >= 0)
	{
		array[ilen--] = n % 10 + '0';
		n /= 10;
	}
	return (array);
}

char			*ft_itoa(int n)
{
	int			ilen;
	char		*array;
	long int	ne;

	ilen = ft_intlen(n);
	ne = n;
	if (n < 0)
	{
		ne = -ne;
		if (!(array = (char*)malloc(sizeof(char) * ilen + 2)))
			return (NULL);
		array[0] = '-';
		array[ilen + 1] = '\0';
		while (ilen > 0)
		{
			array[ilen--] = ne % 10 + '0';
			ne = ne / 10;
		}
	}
	else
	{
		array = ft_positive(n, ilen);
	}
	return (array);
}
