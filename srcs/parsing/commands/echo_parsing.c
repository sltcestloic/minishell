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

void	parse_env_var(t_command *cmd, int i)
{
	char	*var = get_env_var(cmd->shell, cmd->args[i]);

	if (var)
		cmd->args[i] = var;
	else
	{
		while (cmd->args[i + 1])
		{
			cmd->args[i] = cmd->args[i + 1];
			i++;
		}
		free(cmd->args[i]);
		cmd->args[i] = 0;
	}
}

char	*compute_args(t_command *cmd, int has_n)
{
	char	*ret;
	char	*swap;
	int		i;

	i = -1;
	if (ft_splitlen(cmd->args) == 0)
		return (NULL);
	ret = malloc(1);
	*ret = 0;
	if (has_n)
		i++;
	while (cmd->args[++i])
	{
		printf("%d\n", i);
		if (cmd->args[i][0] == '$')
			parse_env_var(cmd, i);
		if (ft_strlen(ret))
		{
			swap = ft_strjoin(ret, " ");
			free(ret);
			ret = swap;
		}
		if (cmd->args[i])
		{
			swap = ft_strjoin(ret, cmd->args[i]);
			free(ret);
			ret = swap;
		}
	}
	return (ret);
}

void	parse_echo(t_command *cmd)
{
	char	*args;
	int		has_n;

	if (ft_splitlen(cmd->args))
		has_n = ft_strcmp(cmd->args[0], "-n") == 0;
	else
		has_n = FALSE;
	args = compute_args(cmd, has_n);
	echo(args, has_n);
}
