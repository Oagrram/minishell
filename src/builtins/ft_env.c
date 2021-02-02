/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oagrram <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:24:59 by oagrram           #+#    #+#             */
/*   Updated: 2021/01/29 15:25:00 by oagrram          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../includes/minishell.h"

int			ft_env(t_env *head)
{
	while (head->next)
	{
		ft_putstr(head->name);
		ft_putchar('=');
		if (!head->value)
			ft_putendl("");
		else
			ft_putendl(head->value);
		head = head->next;
	}
	return (0);
}
