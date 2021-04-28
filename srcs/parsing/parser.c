#include "minishell.h"

char	*get_env_var(t_shell *shell, char *str)
{
	t_envlst	*lst;
	char		*ret;
	char		**split;
	char		*name;

	split = ft_split(str, ' ');
	name = ft_strtrim(&split[0][1], " \"'");
	lst = shell->env_var;
	ret = malloc(1);
	*ret = 0;
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			free(ret);
			ret = ft_strdup(lst->value);
			break ;
		}
		lst = lst->next;
	}
	free_split(split);
	return (ret);
}

char	**get_command_args(char	*input)
{
	char	**ret;
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*input)
		return (NULL);
	split = ft_split(input, ' ');
	ret = malloc(sizeof(char *) * (ft_splitlen(split) + 1));
	while (split[i])
	{
		ret[j++] = ft_strdup(split[i]);
		i++;
	}
	ret[j] = 0;
	free_split(split);
	return (ret);
}

t_command	parse_command(char *input, t_shell *shell)
{
	t_command	cmd;

	cmd.args = get_command_args(input);
	cmd.shell = shell;
	return (cmd);
}

void	handle_cmd(char *input, t_shell *shell)
{
	t_command	cmd;

	cmd = parse_command(input, shell);
	if (ft_strcmp("exit", cmd.args[0]) == 0)
		ft_exit(shell->to_free);
	else if (ft_strcmp("echo", cmd.args[0]) == 0)
		parse_echo(&cmd);
	else if (ft_strcmp("env", cmd.args[0]) == 0)
		env(shell->env_var);
	else if (ft_strcmp("export", cmd.args[0]) == 0)
	{
		if (!cmd.args[0])
			export(shell->env_var);
		else
			new_env_elem(cmd.args[1], shell);
	}
	else if (ft_strcmp("cd", cmd.args[0]) == 0)
	{
		if (!cmd.args[0])
			change_pwd(shell, 0);
		else if (ft_splitlen(cmd.args) > 2)
			write(1, "cd: too many arguments\n", 24);
		else
			change_pwd(shell, cmd.args[0]);
	}
	else if (ft_strcmp("pwd", cmd.args[0]) == 0)
		pwd(shell);
	else
		to_exec(shell, cmd.args);
	free(cmd.args);
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	cat_var(t_parser *parser, char *var, char *input, t_index *indx)
{
	char	*swap;

	swap = malloc(ft_strlen(input) + ft_strlen(var));
	ft_strcpy(swap, parser->parsed_input);
	ft_strcat(swap, var);
	free(parser->parsed_input);
	parser->parsed_input = swap;
	indx->k = ft_strlen(parser->parsed_input);
	while (input[indx->i] && input[indx->i] != ' ')
		indx->i++;
	indx->i -= 2;
}

void	add_separator(t_parser *parser, int indx)
{
	int	i;

	i = 0;
	while (parser->separators[i])
		i++;
	parser->separators[i] = indx;
	parser->separators[i + 1] = 0;
	parser->has_cmd = 0;
}

int	treat_input(t_shell *shell, char *input, t_parser *parser)
{
	t_index	i;
	char	*var;

	i = init_index();
	while (input[i.i])
	{
		if (input[i.i] == '\'')
		{
			if (!parser->d_quote && !parser->backslash)
				parser->s_quote = !parser->s_quote;
			else
				parser->parsed_input[i.k++] = input[i.i];
		}
		else if (input[i.i] == '"')
		{
			if (!parser->s_quote && !parser->backslash)
				parser->d_quote = !parser->d_quote;
			else
				parser->parsed_input[i.k++] = input[i.i];
			parser->backslash = 0;
		}
		else if (input[i.i] == '$' && !parser->backslash && !parser->s_quote)
		{
			var = get_env_var(shell, &input[i.i]);
			if (ft_strlen(var))
				cat_var(parser, var, input, &i);
			else
			{
				free(var);
				while (input[i.i + 1] && ft_isalnum(input[i.i + 1]))
					i.i++;
			}
		}
		else if (input[i.i] == ';')
		{
			if (!parser->s_quote && !parser->d_quote && !parser->backslash)
			{
				if (parser->has_cmd)
					add_separator(parser, i.k);
				else
				{
					ft_putstr_fd("syntax error near unexpected token `;'\n", 1);
					return (0);
				}
			}
			parser->parsed_input[i.k++] = input[i.i];
		}
		else if (input[i.i] == '\\')
		{
			if (parser->s_quote || parser->backslash || (!is_quote(input[i.i + 1]) && input[i.i + 1] != ';'))
				parser->parsed_input[i.k++] = input[i.i];
			if (!parser->s_quote)
				parser->backslash = !parser->backslash;
		}
		else
		{
			parser->backslash = 0;
			parser->parsed_input[i.k++] = input[i.i];
			parser->has_cmd = 1;
		}
		i.i++;
	}
	parser->parsed_input[i.k] = 0;
	if (parser->s_quote || parser->d_quote)
	{
		ft_putstr_fd("Error: quote not closed\n", 1);
		*parser->parsed_input = 0;
	}
	return (1);
}

void	parse_input(char *input, t_shell *shell)
{
	char		**split;
	int			i;
	t_parser	parser;

	parser = init_parser(input);
	if (!treat_input(shell, input, &parser))
	{
		free(parser.parsed_input);
		free(parser.separators);
		return ;
	}
	i = 0;
	split = ft_splitcmds(parser.parsed_input, &parser);
	free(parser.parsed_input);
	free(parser.separators);
	while (split[i])
	{
		handle_cmd(split[i], shell);
		i++;
	}
	free_split(split);
}
