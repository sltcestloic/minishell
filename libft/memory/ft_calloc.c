/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:31:07 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:53:53 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;
	size_t	total;

	total = count * size;
	array = malloc(total);
	if (!array)
		return (NULL);
	ft_memset(array, 0, total);
	return (array);
}
