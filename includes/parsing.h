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
t_parser	init_parser(char *input);
t_index		init_index(void);

/*
** Commands parsing
*/

void		parse_echo(t_command *cmd);

int			count_cmds(t_parser *parser);
char		**ft_splitcmds(const char *str, t_parser *parser);

#endif