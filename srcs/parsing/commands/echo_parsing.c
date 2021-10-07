#include "minishell.h"

char	*compute_args(char **args, int has_n)
{
	char	*ret;
	char	*swap;
	int		i;

	i = 0;
	if (ft_splitlen(args) == 0)
		return (NULL);
	ret = malloc(1);
	*ret = 0;
	if (has_n)
		i++;
	while (args[++i])
	{
		swap = ft_strjoin(ret, args[i]);
		free(ret);
		ret = swap;
		swap = ft_strjoin(ret, " ");
		free(ret);
		ret = swap;
	}
	return (ret);
}

void	parse_echo(char **input)
{
	char	*args;
	int		has_n;

	if (ft_splitlen(input) > 1)
		has_n = ft_strcmp(input[1], "-n") == 0;
	else
		has_n = FALSE;
	args = compute_args(input, has_n);
	//echo(args, has_n);
}
