#include "minishell.h"

char	*get_env_var(t_shell *shell, char *str)
{
	(void)shell;
	char *ret = malloc(4);
	ft_strlcpy(ret, "test", 5);
	if (ft_strcmp(str, "$TEST") == 0)
		return (ret);
	else return NULL;
}

char	**get_command_args(char	*input, t_shell *shell)
{
	char	**ret;
	char	**split;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*input)
		return (NULL);
	split = ft_splitcmds(input, ' ', 1);
	ret = malloc(sizeof(char *) * (ft_splitlen(split) + 1));
	while (split[i])
	{
		if (split[i][0] == '$')
		{
			var = get_env_var(shell, split[i]);
			if (var != NULL)
				ret[j++] = var;				
			else
				free(var);
			i++;
			continue ;			
		}
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

	cmd.args = get_command_args(input, shell);
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
		else if (ft_splitlen(cmd.args) > 1)
			write(1, "cd: too many arguments\n", 24);
		else
			change_pwd(shell, cmd.args[0]);
	}
	else if (ft_strcmp("pwd", cmd.args[0]) == 0)
		pwd(shell);
	free(cmd.args);
}

void	parse_input(char *input, t_shell *shell)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_splitcmds(input, ';', 0);
	while (split[i])
	{
		handle_cmd(split[i], shell);
		i++;
	}
	free_split(split);
}
