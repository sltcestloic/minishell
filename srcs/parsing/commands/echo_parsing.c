#include "minishell.h"

char	*compute_args(t_command *cmd, int has_n)
{
	char	*ret;
	char	*swap;
	int		i;

	i = 0;
	if (ft_splitlen(cmd->args) == 0)
		return (NULL);
	ret = malloc(1);
	*ret = 0;
	if (has_n)
		i++;
	while (cmd->args[++i])
	{
		swap = ft_strjoin(ret, cmd->args[i]);
		free(ret);
		ret = swap;
		swap = ft_strjoin(ret, " ");
		free(ret);
		ret = swap;
	}
	return (ret);
}

void	parse_echo(t_command *cmd)
{
	char	*args;
	int		has_n;

	if (ft_splitlen(cmd->args))
		has_n = ft_strcmp(cmd->args[1], "-n") == 0;
	else
		has_n = FALSE;
	for (int i = 0; cmd->args[i]; i++)
		printf("%d: %s\n", i, cmd->args[i]);
	args = compute_args(cmd, has_n);
	echo(args, has_n);
}
