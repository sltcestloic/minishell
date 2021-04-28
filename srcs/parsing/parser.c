#include "minishell.h"

char	**get_command_args(char	*input)
{
	char	**ret;
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*input)
		return (NULL);
	split = ft_split(input, ' ');
	ret = malloc(sizeof(char *) * (ft_splitlen(split) + 1));
	while (split[i])
	{
		ret[j++] = ft_strdup(split[i]);
		i++;
	}
	ret[j] = 0;
	free_split(split);
	return (ret);
}

t_command	parse_command(char *input, t_shell *shell)
{
	t_command	cmd;

	cmd.args = get_command_args(input);
	cmd.shell = shell;
	return (cmd);
}

void	handle_cmd(char *input, t_shell *shell)
{
	t_command	cmd;

	cmd = parse_command(input, shell);
	if (ft_strcmp("exit", cmd.args[0]) == 0)
		ft_exit(shell->to_free);
	else if (ft_strcmp("echo", cmd.args[0]) == 0)
		parse_echo(&cmd);
	else if (ft_strcmp("env", cmd.args[0]) == 0)
		env(shell->env_var);
	else if (ft_strcmp("export", cmd.args[0]) == 0)
	{
		if (!cmd.args[0])
			export(shell->env_var);
		else
			new_env_elem(cmd.args[1], shell);
	}
	else if (ft_strcmp("cd", cmd.args[0]) == 0)
	{
		if (!cmd.args[0])
			change_pwd(shell, 0);
		else if (ft_splitlen(cmd.args) > 2)
			write(1, "cd: too many arguments\n", 24);
		else
			change_pwd(shell, cmd.args[0]);
	}
	else if (ft_strcmp("pwd", cmd.args[0]) == 0)
		pwd(shell);
	else
		to_exec(shell, cmd.args);
	free(cmd.args);
}

void	parse_input(char *input, t_shell *shell)
{
	char		**split;
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
	split = ft_splitcmds(parser.parsed_input, &parser);
	free(parser.parsed_input);
	free(parser.separators);
	while (split[i])
	{
		handle_cmd(split[i], shell);
		i++;
	}
	free_split(split);
}
