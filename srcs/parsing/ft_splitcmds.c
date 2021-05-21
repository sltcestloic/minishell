#include "minishell.h"

/*
** TODO: >> 
*/
static int	get_type(char c)
{
	if (c == '>')
		return (3);
	else if (c == '<')
		return (2);
	else if (c == '|')
		return (5);
	else if (c == ';')
		return (6);
	else
		return (-1);
}

void print_cmd(t_cmd *cmd)
{
	t_cmd *current = cmd; 									/*			*/
	while (current)											/*			*/
	{														/*			*/
		printf("-------------------\n");					/*			*/
		printf("type: %d\n", current->type);				/*			*/
		if (current->value)									/*			*/
		{													/*   DEBUG	*/
			printf("value:\n");								/*			*/
			for (int k = 0; current->value[k]; k++)			/*			*/
				printf("%s\n", current->value[k]);			/*			*/
		}													/*			*/
		current = current->next;							/*			*/
	}														/*			*/
	printf("-------------------\n"); 						/*			*/
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
	free(ret);
	return (cmd);
}

char	**get_content(const char *str, int start, int end)
{
	char	*ret;
	char	*swap;
	char	**rett;
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
	rett = ft_split(ret, ' ');
	free(ret);
	return (rett);
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
	t_cmd	*next;
	t_index	i;
	int		last;

	cmd = malloc(sizeof(t_cmd));
	cmd->type = -1;
	cmd->next = NULL;
	i = init_index();
	i.i = -1;
	if (!str)
		return (NULL);
	while (parser->separators[++i.i])
	{
		last = cmd_last_type(cmd);
		if (last == 2 || last == 3)
			cmd_last(cmd)->value = get_content(str, i.j, parser->separators[i.i] - 1);
		else
		{
			cmd_addback(cmd, ft_argdup(str, i.j, parser->separators[i.i] - 1));
			if (get_type(str[parser->separators[i.i]]) != -1)
			{
				next = malloc(sizeof(t_cmd));
				next->type = get_type(str[parser->separators[i.i]]);
				cmd_addback(cmd, next);
			}
		}
		i.j = parser->separators[i.i] + 1;
	}
	last = cmd_last_type(cmd);
	if (last == 2 || last == 3)
		cmd_last(cmd)->value = get_content(str, i.j, ft_strlen(str));
	else
		cmd_addback(cmd, ft_argdup(str, i.j, ft_strlen(str)));
	//print_cmd(cmd);
	return (cmd);
}
