/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 10:24:50 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/17 13:09:32 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(t_shell *shell)
{
	write(1, GREEN, ft_strlen(GREEN));
	write(1, "user@minishell", 14);
	write(1, RESET, ft_strlen(RESET));
	write(1, " - ", 3);
	write(1, BLUE, ft_strlen(BLUE));
	pwd(shell);
	write(1, RESET, ft_strlen(RESET));
	write(1, "$ ", 2);
}
