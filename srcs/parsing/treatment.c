#include "minishell.h"

/*
** TODO: trouver comment faire pour >> 
*/
static int	is_interpretable(char c)
{
	return (c == '\'' || c == '"' || c == '$' || c == ';'
		|| c == '>' || c == '<' || c == '|');
}

static int	is_separator(char c)
{
	return (c == ';' || c == '>' || c == '<' || c == '|');
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

/*
** TODO: ajouter > >> < | aux separateurs, puis au moment du split 
** regarder le type du separateur et le mettre dans la structure en fonction 
*/
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
		else if (is_separator(input[i.i]))
		{
			if (!parser->s_quote && !parser->d_quote && !parser->backslash)
			{
				if (parser->has_cmd)
					add_separator(parser, i.k);
				else
				{
					ft_putstr_fd("syntax error\n", 1);
					return (0);
				}
			}
			parser->parsed_input[i.k++] = input[i.i];
		}
		else if (input[i.i] == '\\')
		{
			if (parser->s_quote || parser->backslash || !is_interpretable(input[i.i + 1]))
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
