/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <midoxthex@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:42:42 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/19 18:56:11 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				i;
	int				negative;
	unsigned int	number;

	negative = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		negative = 1;
		str++;
	}
	else if (*str == '+')
		str++;
	number = 0;
	i = *str - '0';
	while (i >= 0 && i <= 9 && *str != '\0')
	{
		number = number * 10 + i;
		str++;
		i = *str - '0';
	}
	if (negative)
		number = number * -1;
	return (number);
}
