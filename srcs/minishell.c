#include "minishell.h"

t_cmd	*cmd_init(void)
{
	t_cmd *in;
	t_cmd *out;
	t_cmd *cmd;
	t_cmd *out2;
	char **cat;

	cat = malloc(sizeof(char*) * 2);
	cat[0] = malloc(4);
	cat[1] = 0;
	cat[0][0] = 'c';
	cat[0][1] = 'a';
	cat[0][2] = 't';
	cat[0][3] = 0;
	in = malloc(sizeof(t_cmd));
	out = malloc(sizeof(t_cmd));
	out2 = malloc(sizeof(t_cmd));
	cmd = malloc(sizeof(t_cmd));
	cmd->next = in;
	in->next = out;
	out->next = out2;
	out2->next = 0;
	cmd->type = 1;
	in->type = 2;
	out->type = 3;
	out2->type = 3;
	cmd->value = cat;
	in->value = malloc(sizeof(char*) * 2);
	out->value = malloc(sizeof(char*) * 2);
	out2->value = malloc(sizeof(char*) * 2);
	in->value[0] = ft_strdup("Makefile");
	in->value[1] = ft_strdup("");
	out->value[0] = ft_strdup("Test");
	out->value[1] = ft_strdup("");
	out2->value[0] = ft_strdup("Testo");
	out2->value[1] = ft_strdup("");
	return (cmd);
}

void	test_redirect(t_shell *shell)
{
	t_cmd *cmd;

	cmd = cmd_init();
	redirect(cmd);
	to_exec(shell, cmd->value);
}

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
	display_prompt(shell);
	// test_redirect(shell);
	while (ft_get_next_line(0, &input) > 0)
	{
		parse_input(input, shell);
		display_prompt(shell);
		free(input);
	}
	free(input);
}
