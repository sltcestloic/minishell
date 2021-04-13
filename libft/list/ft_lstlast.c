/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:33:07 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:52:13 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *list)
{
	t_list	*next;

	next = list;
	if (!next)
		return (NULL);
	while (1)
	{
		if (!next->next)
			return (next);
		next = next->next;
	}
	return (NULL);
}
