#include "minishell.h"

/* void	handle_cmd(char **input, t_shell *shell)
{
	int	i;

	i = 1;
	if (ft_strcmp("exit", input[0]) == 0)
		ft_exit(shell->to_free);
	else if (ft_strcmp("echo", input[0]) == 0)
		parse_echo(input);
	else if (ft_strcmp("env", input[0]) == 0)
		env(shell->env_var);
	else if (ft_strcmp("unset", input[0]) == 0)
	{
		while (input[i])
		{
			remove_env_elem(input[i], shell);
			i++;
		}
	}
	else if (ft_strcmp("export", input[0]) == 0)
	{
		if (!input[1])
			export(shell->env_var);
		else
		{
			while (input[i])
			{
				new_env_elem(input[i], shell);
				i++;
			}
		}
	}
	else if (ft_strcmp("cd", input[0]) == 0)
	{
		if (!input[0])
			change_pwd(shell, 0);
		else if (ft_splitlen(input) > 2)
			write(1, "cd: too many arguments\n", 24);
		else
			change_pwd(shell, input[0]);
	}
	else if (ft_strcmp("pwd", input[0]) == 0)
		pwd(shell);
	else
		to_exec(shell, input);
	free(input);
} */

void	add_new_cmd(t_cmd *cmd)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
		cmd_free(cmd); //TODO free correctement
		return ;
	}
	cmd_last(cmd)->next = new_cmd;
}

int		count_args(char *input)
{
	t_parser	parser;
	int			i;
	int			result;

	parser.s_quote = 0;
	parser.d_quote = 0;
	i = 0;
	result = 0;
	while (input[i])
	{
		if (ft_iswhitespace(input[i] && !parser.s_quote && !parser.d_quote))
			result++;
		else if (input[i] == '"' && !parser.s_quote)
			parser.d_quote = !parser.d_quote;
		else if (input[i] == '\'' == !parser.d_quote)
			parser.s_quote = !parser.s_quote;
		else if (input[i] == '|')
		{
			if (ft_iswhitespace(input[i - 1]))
				result--;
			break ;
		}
		i++;
	}
	return (result);
}

t_index	get_next_arg(char *input, int *i)
{
	t_index		index;
	t_parser	parser;

	index.i = *i;
	parser.d_quote = 0;
	parser.s_quote = 0;
	while (ft_iswhitespace(input[*i]))
		(*i)++;
	while (input[*i])
	{
		if (ft_iswhitespace(input[*i] && !parser.s_quote && !parser.d_quote))
			break ;
		else if (input[*i] == '"' && !parser.s_quote)
			parser.d_quote = !parser.d_quote;
		else if (input[*i] == '\'' == !parser.d_quote)
			parser.s_quote = !parser.s_quote;
		(*i)++;
	}
	index.j = *i;
	return (index);
}


int	set_cmd_content(t_cmd *cmd, char *input, int *i)
{
	t_index		idx;
	t_parser	parser;

	idx.i = 0;
	idx.j = 1;
	parser.s_quote = 0;
	parser.d_quote = 0;
	cmd->value = malloc(sizeof(char *) * (count_args(&input[*i]) + 1));
	if (!cmd->value)
		return (0);
	while (input[*i] && input[*i] != '|' && !ft_iswhitespace(input[*i]))
	{
		(*i)++;
		idx.i++;
	}
	cmd->value[0] = ft_strrdup(input, *i - idx.i, *i);
	idx.i = *i;
	while (input[*i])
	{
		if (!parser.s_quote && !parser.d_quote)
		{
			if (input[*i] == '|' )
			{
				(*i)--; //pour que parse_input puisse lire le | et ajouter une cmd
				break;
			}
			if (ft_iswhitespace(input[*i]))
				cmd->value[idx.j++] = ft_strrdup(input, idx.i, *i - 1);
		}
		(*i)++;
	}
	return (1);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	return (ret);
}

void	parse_input(char *input, t_shell *shell)
{
	t_cmd		*cmd;
	int			i;
	t_parser	*parser;

	(void)shell;
	parser = init_parser(input);
	i = 0;
	cmd = init_cmd();
	while (input[i]) {
		if (!parser->s_quote && !parser->d_quote)
		{
			parser->redirect = is_redirect(input, &i);
			if (parser->redirect)
			{
				init_redirect(cmd_last(cmd), parser->redirect);
				if (parser->redirect < 3)
					set_file_name(cmd_last(cmd)->out, input, &i);
				else
					set_file_name(cmd_last(cmd)->in, input, &i);
				continue ;
			}
			else if (input[i] == '|')
				add_new_cmd(cmd);
		}
		if (ft_isalnum(input[i]))
		{
			if (!set_cmd_content(cmd_last(cmd), input, &i))
			{
				cmd_free(cmd); //TODO free correctement
				exit(0);
			}
		}
		else if (input[i] == '"' && !parser->s_quote)
			parser->d_quote = !parser->d_quote;
		else if (input[i] == '\'' == !parser->d_quote)
			parser->s_quote = !parser->s_quote;
		i++;
	}
	if (parser->d_quote || parser->s_quote)
		printf("Invalid input: unclosed quote.\n");
	//TODO else send to exec
	free(parser);
	cmd_free(cmd);
}
