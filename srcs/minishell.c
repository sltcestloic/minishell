/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:48:23 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/30 12:33:17 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit = 0;

inline static int	init_shell(t_shell *shell, char **envp)
{
	shell->to_free = 0;
	shell->to_close = 0;
	shell->env_var = 0;
	shell->pwd = ft_malloc(MAXPATHLEN, &shell->to_free);
	shell->envp = envp;
	if (!shell->pwd)
		ft_malloc_error(shell->to_free);
	return (0);
}

static int	is_valid_input(char *input)
{
	int	i;

	i = 0;
	if (ft_strlen(input) == 0)
		return (0);
	while (input[i])
	{
		if (!ft_iswhitespace(input[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	atty_check(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		write(2, "ERROR YOU CAN'T MESS WITH ME !\n", 32);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	shell;

	if (!atty_check(ac, av))
		return (-1);
	if (init_shell(&shell, envp) == -1)
		return (-1);
	set_env(envp, &shell);
	set_pwd(&shell);
	tcgetattr(0, &shell.old);
	while (1)
	{
		signal(SIGINT, &if_sigint);
		set_term(&shell);
		input = readline("\e[0;92mminishell\e[0m$ ");
		if (!input)
			exit_cmd(&shell, NULL, 0);
		if (is_valid_input(input))
		{
			parse_input(input, &shell);
			add_history(input);
		}
		free(input);
	}
}
