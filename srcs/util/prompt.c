/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 10:24:50 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/14 14:55:16 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(void)
{
	write(1, GREEN, ft_strlen(GREEN));
	write(1, "user@minishell", 14);
	write(1, RESET, ft_strlen(RESET));
	write(1, " - ", 3);
	write(1, BLUE, ft_strlen(BLUE));
	write(1, "/Users/lbertran/Desktop/", 24);
	write(1, RESET, ft_strlen(RESET));
	write(1, "$ ", 2);
}
