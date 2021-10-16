#include "minishell.h"

inline static int	init_shell(t_shell **shell, char **envp)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		return (-1);
	(*shell)->to_free = 0;
	(*shell)->env_var = 0;
	(*shell)->pwd = malloc(10000);
	(*shell)->envp = envp;
	if ((*shell)->pwd == 0)
		return (-1);
	return (0);
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
		parse_input(input, shell);
		free(input);
		input = readline("\e[0;92mminishell\e[0m$ ");
	}
}
