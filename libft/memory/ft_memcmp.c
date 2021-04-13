/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 13:56:08 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:54:55 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*array;
	unsigned char	*compare;

	array = (unsigned char *)s1;
	compare = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((*array == *compare) && n - 1)
	{
		array++;
		compare++;
		n--;
	}
	return (*array - *compare);
}
