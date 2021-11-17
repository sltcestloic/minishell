/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:48:23 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/17 08:57:23 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_exit = 0;

inline static int	init_shell(t_shell **shell, char **envp)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		return (-1);
	(*shell)->to_free = 0;
	(*shell)->to_close = 0;
	(*shell)->env_var = 0;
	(*shell)->pwd = ft_malloc(MAXPATHLEN, &(*shell)->to_free);
	(*shell)->envp = envp;
	if ((*shell)->pwd == 0)
		return (-1);
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

static int	is_duplicate(char *str)
{
	HIST_ENTRY	*entry;

	entry = previous_history();
	if (!entry || !entry->line || !str)
		return (0);
	return (ft_strcmp(entry->line, str) == 0);
}

void	set_term(t_shell *shell)
{
	tcgetattr(0, &shell->new);
	shell->new.c_lflag &= ~ECHOCTL;
	shell->new.c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->new);
}

void	unset_term(t_shell *shell)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->old);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*shell;

	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		write(2, "ERROR YOU CAN'T MESS WITH ME !\n", 32);
		return (-1);
	}	
	if (init_shell(&shell, envp) == -1)
		return (-1);
	(void)ac;
	(void)av;
	set_env(envp, shell);
	set_pwd(shell);
	tcgetattr(0, &shell->old);
	while (1)
	{
		signal(SIGINT, &if_sigint);
		set_term(shell);
		input = readline("\e[0;92mminishell\e[0m$ ");
		if (!input)
			parse_input("exit", shell);
		if (is_valid_input(input))
			parse_input(input, shell);
		if (!is_duplicate(input))
			add_history(input);
		free(input);
	}
}
