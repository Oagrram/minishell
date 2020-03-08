/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_btoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:50:23 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/15 18:25:28 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_power(int nbr, int p)
{
	if (p == 0)
		return (1);
	return (nbr * ft_power(nbr, p - 1));
}

int				ft_bonus_btoi(char *bi)
{
	int len;
	int i;
	int	val;

	len = ft_strlen(bi);
	val = 0;
	i = 0;
	while (bi[i] != '\0')
	{
		if (bi[i] == '1')
			val += ft_power(2, len - 1 - i);
		i++;
	}
	return (val);
}
