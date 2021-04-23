#include "minishell.h"

inline static int	init_shell(t_shell **shell, char **envp)
{
	*shell = malloc(sizeof(t_shell));
	if (!*shell)
		return (-1);
	(*shell)->to_free = 0;
	(*shell)->env_var = 0;
	(*shell)->envp = envp;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell *shell;
	char *test[2];

	test[0] = "ls";
	test[1] = 0;

	if (init_shell(&shell, envp) == -1)
		return (-1);
	(void)ac;
	(void)av;
	set_env(envp, shell);
	set_pwd(shell);
	display_prompt(shell);
	while (ft_get_next_line(0, &input) > 0)
	{
		parse_input(input, shell);
		display_prompt(shell);
	}
}

/* int main()
{
	char **test = ft_splitcmds("echo \"test; bonjour\"; echo test; ls -a; grep ';'; test", ';');
	for (int i = 0; test[i]; i++)
		printf("%s\n", test[i]);
	free_split(test);
} */