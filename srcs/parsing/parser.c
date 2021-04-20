#include "minishell.h"

char	*get_command_name(char *input)
{
	char	*ret;
	char	**split;
	int		i;

	i = 0;
	if (*input)
	{
		split = ft_split(input, ' ');	
		ret = malloc(sizeof(char) * (ft_strlen(split[0]) + 1));
		while (split[0][i])
		{
			ret[i] = split[0][i];
			i++;
		}
		ret[i] = '\0';
		free_split(split);
	}
	else
		return (input);
	return (ret);
}

char	**get_command_args(char	*input)
{
	char	**ret;
	char	**split;
	int		i;

	i = 1;
	if (!*input)
		return (NULL);
	split = ft_split(input, ' ');
	ret = malloc(sizeof(char *) * ft_splitlen(split));
	while (split[i])
	{
		ret[i - 1] = ft_strdup(split[i]);
		i++;
	}
	ret[i - 1] = 0;
	free_split(split);
	return (ret);
}

t_command	parse_command(char *input, t_shell *shell)
{
	t_command	cmd;

	cmd.name = get_command_name(input);
	cmd.args = get_command_args(input);
	cmd.shell = shell;
	return (cmd);
}

void	handle_cmd(char *input, t_shell *shell)
{
	t_command	cmd;

 	cmd = parse_command(input, shell);
 	if (ft_strcmp("exit", cmd.name) == 0)
 		ft_exit(shell->to_free);
 	else if (ft_strcmp("echo", cmd.name) == 0)
 		parse_echo(&cmd);
 	else if (ft_strcmp("env", cmd.name) == 0)
 		env(shell->env_var);
 	else if (ft_strcmp("export", cmd.name) == 0)
	{
		if (!cmd.args[0])
 			export(shell->env_var);
		else
			new_env_elem(cmd.args[0], shell);
	}
	else if (ft_strcmp("cd", cmd.name) == 0)
	{
		if (!cmd.args[0])
			change_pwd(shell, NULL);
		else if (ft_splitlen(cmd.args) > 1)
			write(1, "cd: too many arguments\n", 24);
		else
			change_pwd(shell, cmd.args[0]);
	}
 	free(cmd.name);
 	if (cmd.args)
 		free_split(cmd.args);
}

void	parse_input(char *input, t_shell *shell)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_splitcmds(input, ';');
	while (split[i])
	{
		handle_cmd(split[i], shell);
		i++;
	}
}
