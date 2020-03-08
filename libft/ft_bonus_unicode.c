/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_unicode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 21:46:19 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/18 12:24:48 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_power(int nbr, int p)
{
	if (p == 0)
		return (1);
	return (nbr * ft_power(nbr, p - 1));
}

static	int		ft_btoi(char *bi)
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

static	void	ft_print(char *t1, char *t2)
{
	int i;
	int j;

	i = ft_btoi(t1);
	j = ft_btoi(t2);
	write(1, &j, 1);
	write(1, &i, 1);
}

static	void	ft_coded_2(char *bi)
{
	char	*t1;
	char	*t2;
	int		i;
	int		j;

	t1 = (char *)malloc(9);
	t2 = (char *)malloc(9);
	t1[0] = '1';
	t1[1] = '0';
	t2[0] = '1';
	t2[1] = '1';
	t2[2] = '0';
	i = 2;
	j = ft_strlen(bi);
	while (i < 8)
		t1[i++] = bi[j++ - 6];
	i = 7;
	j = ft_strlen(bi);
	while (j > 6)
		t2[i--] = bi[j-- - 7];
	while (i > 2)
		t2[i--] = '0';
	ft_print(t1, t2);
	free(t2);
	free(t1);
}

void			ft_bonus_unicode(int nbr)
{
	char *bi;

	if (nbr > 30 && nbr < 127)
		write(1, &nbr, 1);
	bi = ft_convert_to_binary(nbr);
	if (nbr > 257 && nbr < 2048)
		ft_coded_2(bi);
}
