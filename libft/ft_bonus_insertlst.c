/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_insertlst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elfetoua <elfetoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:09:43 by elfetoua          #+#    #+#             */
/*   Updated: 2019/04/15 18:27:51 by elfetoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bonus_insertlst(t_list *prev_node, const void *content, size_t ct_sz)
{
	t_list *new;

	if (prev_node == NULL)
		return ;
	new = ft_lstnew(content, ct_sz);
	if (!new)
		return ;
	new->next = prev_node->next;
	prev_node->next = new;
}
