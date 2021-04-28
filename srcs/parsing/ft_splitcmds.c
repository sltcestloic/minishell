#include "minishell.h"

char	*ft_argdup(const char *str, int start, int end)
{
	char	*ret;
	char	*swap;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (end - start + 2));
	if (!ret)
		return (NULL);
	while (start <= end)
	{
		ret[i] = str[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	swap = ft_strtrim(ret, " ");
	free(ret);
	ret = swap;
	return (ret);
}

int	count_cmds(t_parser *parser)
{
	int		i;

	i = 1;
	while (parser->separators[i])
		i++;
	return (i);
}

char	**ft_splitcmds(const char *str, t_parser *parser)
{
	char	**ret;
	t_index	i;

	i = init_index();
	i.i = -1;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_cmds(parser) + 2));
	if (!ret)
		return (NULL);
	while (parser->separators[++i.i])
	{
		ret[i.k] = ft_argdup(str, i.j, parser->separators[i.i] - 1);
		i.j = parser->separators[i.i] + 1;
		if (!ret[i.k++])
		{
			free_split(ret);
			return (NULL);
		}
	}
	ret[i.k] = ft_argdup(str, i.j, ft_strlen(str));
	ret[i.k + 1] = NULL;
	return (ret);
}
