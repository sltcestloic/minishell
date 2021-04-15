/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:18:47 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/15 14:56:40 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static int	init_shell(t_shell **shell)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		return (-1);
	(*shell)->to_free = 0;
	(*shell)->env_var = 0;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell *shell;

	if (init_shell(&shell) == -1)
		return (-1);
	(void)ac;
	(void)av;
	set_env(envp, shell);
	display_prompt();
	while (ft_get_next_line(0, &input) > 0)
	{
		parse_input(input);
		display_prompt();
	}
}
