#ifndef PARSING_H
# define PARSING_H
# include "exec.h"

typedef struct s_command
{
	char	**args;
	t_shell	*shell;
}				t_command;

typedef struct s_split
{
	int	quote1;
	int	quote2;
	int	indx;
}				t_split;

typedef struct s_parser
{
	int		s_quote;
	int		d_quote;
	int		has_cmd;
	int		backslash;
	char	*parsed_input;
	int		*separators;
}				t_parser;

typedef struct s_index
{
	int		i;
	int		j;
	int		k;
}				t_index;

void		parse_input(char *input, t_shell *shell);
int			treat_input(t_shell *shell, char *input, t_parser *parser);

/*
** Environment variables
*/

void		cat_var(t_parser *parser, char *var, char *input, t_index *indx);
char		*get_env_var(t_shell *shell, char *str);

/*
** Init
*/

t_parser	init_parser(char *input);
t_index		init_index(void);

/*
** Commands parsing
*/

void		parse_echo(t_command *cmd);

char		**ft_splitcmds(const char *str, t_parser *parser);

#endif