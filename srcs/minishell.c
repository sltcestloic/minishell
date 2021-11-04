#include "minishell.h"

inline static int	init_shell(t_shell **shell, char **envp)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		return (-1);
	(*shell)->to_free = 0;
	(*shell)->to_close = 0;
	(*shell)->last_exit_return = 0;
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

int is_duplicate(char *str)
{
	if (history_length == 0)
		return (0);
	HIST_ENTRY *entry = history_get(history_length);
	return (ft_strcmp(entry->line, str) == 0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*shell;

	if (init_shell(&shell, envp) == -1)
		return (-1);
	(void)ac;
	(void)av;
	set_env(envp, shell);
	set_pwd(shell);
	input = readline("\e[0;92mminishell\e[0m$ ");
	while (input)
	{
		if (is_valid_input(input))
			parse_input(input, shell);
		if (!is_duplicate(input))
			add_history(input);
		free(input);
		input = readline("\e[0;92mminishell\e[0m$ ");
	}
}
