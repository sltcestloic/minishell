/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:18:31 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/01 14:56:50 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (TRUE)
	{
		if (s[i] == (char)c)
			ret = (char *)(s + i);
		if (!s[i])
			break ;
		i++;
	}
	return (ret);
}
