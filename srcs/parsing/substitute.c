#include "minishell.h"

static int	has_env_var(char *input)
{
	t_parser	*parser;
	int			i;

	parser = init_parser();
	i = 0;
	while (input[i])
	{
		if (input[i] == '"' && !parser->s_quote)
			parser->d_quote = !parser->d_quote;
		else if (input[i] == '\'' && !parser->d_quote)
			parser->s_quote = !parser->s_quote;
		else if (input[i] == '$' && !parser->s_quote)
		{
			free(parser);
			return (i);
		}
		i++;
	}
	free(parser);
	return (-1);
}

static char	*substitute_env_var(char *input, int var)
{
	char	*ret;
	char	*var_name;
	char	*new_var;
	int		i;

	ret = NULL;
	printf("input=|%s|\n", input);
	if (var > 0) //dup le debut si la var n'est pas au debut de l'arg
	{
		ret = ft_strrdup(input, 0, var - 1);
		printf("ret avant join: %s\n", ret);
	}
	i = var;
	while (input[i] && (ft_isalnum(input[i]) || i == var)) //i == var pour skip le $
	{
		i++;
	}
	printf("var len: %d\n", i - var);
	var_name = malloc(sizeof(char *) * (i - var));
	new_var = ft_strdup("test_var!"); //TODO recuperer la vraie valeur de la variable
	ret = ft_strjoin(ret, new_var);
	printf("ret: |%s|\n", ret);
	return (ret);
}

/*
** idx.k = var $ index
*/
static void	substitute_env_vars(t_cmd *cmd)
{
	t_index idx;
	char	*tmp;

	idx.i = 0;
	idx.j = 0;
	while (cmd->value[idx.i])
	{
		idx.k = has_env_var(cmd->value[idx.i]);
		printf("var: %d\n", idx.k);
		if (idx.k != -1)
		{
			tmp = substitute_env_var(cmd->value[idx.i], idx.k);
			free(cmd->value[idx.i]);
			cmd->value[idx.i] = tmp;
			continue ; //continue sur cette value tant que idx.k != 0 donc qu'il reste une variable dans la value
		}
		idx.i++;
	}
	return ;
}

static void	substitute_quotes(t_cmd *cmd)
{
	t_index idx;
	char	*new_value;

	idx.i = 0;
	idx.j = 0;
	idx.k = 0;
	while (cmd->value[idx.i])
	{
		new_value = malloc(sizeof(char) * (ft_strlen(cmd->value[idx.i]) + 1));
		if (!new_value)
			return ; //TODO exit ?
		while (cmd->value[idx.i][idx.j])
		{
			if (cmd->value[idx.i][idx.j] != '\'' && cmd->value[idx.i][idx.j] != '"')
				new_value[idx.k++] = cmd->value[idx.i][idx.j];
			new_value[idx.k] = 0;
			idx.j++;
		}
		free(cmd->value[idx.i]);
		cmd->value[idx.i] = new_value;
		idx.i++;
		idx.j = 0;
		idx.k = 0;
	}
}

void	substitute(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		substitute_env_vars(cmd);
		substitute_quotes(cmd);
		tmp = tmp->next;
	}
}