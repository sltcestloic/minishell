/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:28:17 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:52:27 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *list)
{
	size_t	count;
	t_list	*next;

	count = 0;
	next = list;
	while (next)
	{
		next = next->next;
		count++;
	}
	return (count);
}
