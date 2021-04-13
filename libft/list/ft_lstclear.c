/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:39:14 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:52:04 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **list, void (*del)(void*))
{
	t_list	*swap;

	if (!list)
		return ;
	if (!*list)
		return ;
	if (!del)
		return ;
	while (*list)
	{
		swap = (*list)->next;
		(*del)((*list)->content);
		free(*list);
		*list = swap;
	}
}
