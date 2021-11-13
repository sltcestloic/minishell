/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:21:02 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/13 14:47:37 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr, t_free *to_free)
{
	char	*ret;
	int		neg;
	int		len;
	long	nb;

	nb = nbr;
	neg = nb < 0;
	len = ft_intlen(nb);
	ret = ft_malloc(sizeof(char) * (len + 1), &to_free);
	if (!ret)
		ft_malloc_error(to_free);
	if (!ret)
		return (NULL);
	ft_bzero(ret, len + 1);
	if (neg)
	{
		ret[0] = '-';
		nb = -nb;
	}
	while (len-- > neg)
	{
		ret[len] = nb % 10 + 48;
		nb /= 10;
	}
	return (ret);
}
