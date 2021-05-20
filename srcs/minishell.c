#include "minishell.h"

t_cmd	*cmd_init_pipe(void)
{
	t_cmd *in;
	t_cmd *pipe;
	t_cmd *pipe2;
	t_cmd *cmd;
	t_cmd *cmd2;
	t_cmd *cmd3;
	char **cat;

	cat = malloc(sizeof(char*) * 3);
	cat[0] = ft_strdup("cat");
	cat[1] = ft_strdup("Makefile");
	cat[2] = 0;
	cmd = malloc(sizeof(t_cmd));
	cmd->value = cat;
	cmd->type = 1;
	in = malloc(sizeof(t_cmd));
	in->type = 2;
	in->value = malloc(sizeof(char*) * 2);
	in->value[0] = ft_strdup("Makefile");
	in->value[1] = NULL;
	pipe = malloc(sizeof(t_cmd));
	pipe->value = 0;
	pipe->type = 5;
	pipe2 = malloc(sizeof(t_cmd));
	pipe2->value = 0;
	pipe2->type = 5;
	cmd2 = malloc(sizeof(t_cmd));
	cmd2->value = cat;
	cmd2->next = 0;
	cmd2->type = 1;
	cmd3 = malloc(sizeof(t_cmd));
	cmd3->value = cat;
	cmd3->next = 0;
	cmd3->type = 1;
	pipe->next = cmd2;
	cmd2->next = pipe2;
	pipe2->next = cmd3;
	in->next = pipe;
	cmd->next = pipe;
	in = cmd;
	while (in)
	{
		if (in->value)
			printf("%s->", in->value[1]);
		else
			printf("pipe->");
		in = in->next;
	}
	printf("\n");
	return (cmd);
}

void	test_pipe(t_shell *shell)
{
	t_cmd *cmd;

	cmd = cmd_init_pipe();
	cmd_parse(cmd, shell);
}

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
	out->type = 4;
	out2->type = 3;
	cmd->value = cat;
	in->value = malloc(sizeof(char*) * 2);
	out->value = malloc(sizeof(char*) * 2);
	out2->value = malloc(sizeof(char*) * 2);
	in->value[0] = ft_strdup("Makefile");
	in->value[1] = NULL;
	out->value[0] = ft_strdup("Test");
	out->value[1] = NULL;
	out2->value[0] = ft_strdup("Testo");
	out2->value[1] = NULL;
	return (cmd);
}

void	test_redirect_append(t_shell *shell)
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
	//set_env(envp, shell);
	//set_pwd(shell);
	init_fd(shell);
	//display_prompt(shell);
	// test_redirect_append(shell);
	// test_pipe(shell);
	while (ft_get_next_line(0, &input) > 0)
	{
		parse_input(input, shell);
		//display_prompt(shell);
		free(input);
	}
	free(input);
}
