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
	int		i;
	int		start;
	int		wc;

	i = -1;
	start = 0;
	wc = 0;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_cmds(parser) + 2));
	if (!ret)
		return (NULL);
	while (parser->separators[++i])
	{
		ret[wc] = ft_argdup(str, start, parser->separators[i] - 1);
		start = parser->separators[i] + 1;
		if (!ret[wc++])
		{
			free_split(ret);
			return (NULL);
		}
	}
	ret[wc] = ft_argdup(str, start, ft_strlen(str));
	ret[wc + 1] = NULL;
	return (ret);
}
