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
	set_pwd(shell);
	display_prompt(shell);
	while (ft_get_next_line(0, &input) > 0)
	{
		parse_input(input, shell);
		display_prompt(shell);
		free(input);
	}
	free(input);
}

/* int main()
{
	char **test = ft_splitcmds("echo \"test; bonjour\"; echo test; ls -a; grep ';'; test", ';');
	for (int i = 0; test[i]; i++)
		printf("%s\n", test[i]);
	free_split(test);
} */