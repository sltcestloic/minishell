#include "minishell.h"

void	handle_cmd(char **input, t_shell *shell)
{
	int	i;

	i = 1;
	if (ft_strcmp("exit", input[0]) == 0)
		ft_exit(shell->to_free);
	else if (ft_strcmp("echo", input[0]) == 0)
		parse_echo(input);
	else if (ft_strcmp("env", input[0]) == 0)
		env(shell->env_var);
	else if (ft_strcmp("unset", input[0]) == 0)
	{
		while (input[i])
		{
			remove_env_elem(input[i], shell);
			i++;
		}
	}
	else if (ft_strcmp("export", input[0]) == 0)
	{
		if (!input[1])
			export(shell->env_var);
		else
		{
			while (input[i])
			{
				new_env_elem(input[i], shell);
				i++;
			}
		}
	}
	else if (ft_strcmp("cd", input[0]) == 0)
	{
		if (!input[0])
			change_pwd(shell, 0);
		else if (ft_splitlen(input) > 2)
			write(1, "cd: too many arguments\n", 24);
		else
			change_pwd(shell, input[0]);
	}
	else if (ft_strcmp("pwd", input[0]) == 0)
		pwd(shell);
	else
		to_exec(shell, input);
	free(input);
}

void	parse_input(char *input, t_shell *shell)
{
	t_cmd		*cmd;
	int			i;
	t_parser	parser;

	parser = init_parser(input);
	if (!treat_input(shell, input, &parser))
	{
		free(parser.parsed_input);
		free(parser.separators);
		return ;
	}
	i = 0;
	cmd = ft_splitcmds(parser.parsed_input, &parser);
	free(parser.parsed_input);
	free(parser.separators);
	while (cmd)
	{
		if (cmd->type != -1)
		{
			/* printf("handle type %d\n", cmd->type);
			if (cmd->type == 1)
				printf("cmd: %s\n", cmd->value[0]); */
			cmd_parse(cmd, shell);
		/* 	if (cmd->type == 1)
			handle_cmd(cmd->value, shell); */
		}
		cmd = cmd->next;
	}
	cmd_free(cmd);
}
