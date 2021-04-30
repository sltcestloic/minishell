#include "minishell.h"

/*
** TODO: >> 
*/
static int	get_type(char c)
{
	if (c == '>')
		return (2);
	else if (c == '<')
		return (3);
	else if (c == '|')
		return (5);
	else
		return (-1);
}

/*
**	TODO: return une t_cmd avec le contenu et en next le type du
** 	separateur si il y en a un
*/
t_cmd	*ft_argdup(const char *str, int start, int end)
{
	t_cmd	*cmd;
	char	*ret;
	char	*swap;
	int		i;

	cmd = malloc(sizeof(t_cmd));
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
	cmd->type = 1;
	cmd->value = ft_split(ret, ' ');
	if (get_type(str[end + 1]) != -1)
	{
		cmd->next = malloc(sizeof(t_cmd));
		cmd->next->type = get_type(str[end + 1]);
	}
	return (cmd);
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
	t_cmd	*cmd; //ret
	char	**ret;
	t_index	i;

	cmd = malloc(sizeof(t_cmd));
	i = init_index();
	i.i = -1;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_cmds(parser) + 2));
	if (!ret)
		return (NULL);
	while (parser->separators[++i.i])
	{
		//add back ft_argdup a cmd
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
