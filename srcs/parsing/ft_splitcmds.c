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
	free(ret);
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

t_cmd	*ft_splitcmds(const char *str, t_parser *parser)
{
	t_cmd	*cmd;
	t_index	i;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = -1;
	i = init_index();
	i.i = -1;
	if (!str)
		return (NULL);
	while (parser->separators[++i.i])
	{
		cmd_addback(cmd, ft_argdup(str, i.j, parser->separators[i.i] - 1));
		i.j = parser->separators[i.i] + 1;
	}
	cmd_addback(cmd, ft_argdup(str, i.j, ft_strlen(str)));
	/* t_cmd *current = cmd; //DEBUG
	while (current)
	{
		printf("type: %d\n", current->type);
		if (current->value)
		{
			printf("value:\n");
			for (int k = 0; current->value[k]; k++)
				printf("%s\n", current->value[k]);
		}
		current = current->next;
	} */
	return (cmd);
}
