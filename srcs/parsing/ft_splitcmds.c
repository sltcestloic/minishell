#include "minishell.h"

int	is_separator(int indx, t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->separators[i])
	{
		if (parser->separators[i] == indx)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	get_cmd_start(const char *str, t_parser *parser, int i)
{
	while (str[i])
	{
		if (is_separator(i, parser))
			break ;
		if (i == 0)
		{
			i = -1;
			break ;
		}
		i--;
	}
	i += 1;
	return (i);
}

char	*ft_argdup(const char *str, int start, int end)
{
	char	*ret;
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
	int		wc;

	i = -1;
	wc = 0;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_cmds(parser) + 1));
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (!is_separator(i, parser) && (is_separator(i + 1, parser) || !str[i + 1]))
		{
			ret[wc] = ft_argdup(str, get_cmd_start(str, parser, i), i);
			if (!ret[wc++])
			{
				free_split(ret);
				return (NULL);
			}
		}
	}
	ret[wc] = 0;
	return (ret);
}
