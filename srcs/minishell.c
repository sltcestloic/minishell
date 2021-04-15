/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:18:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/15 13:19:48 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)ac;
	(void)av;
	env(envp);
	while (ft_get_next_line(0, &input) > 0)
	{
		parse_input(input);
		display_prompt();
	}
}
