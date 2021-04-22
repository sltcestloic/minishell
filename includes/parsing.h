#ifndef PARSING_H
# define PARSING_H
# include "exec.h"

typedef struct s_command
{
				char	*name;
				char	**args;
				t_shell	*shell;
}				t_command;

typedef struct s_split
{
			int	quote1;
			int	quote2;
}				t_split;

void	parse_input(char *input, t_shell *shell);

/*
** Commands parsing
*/

void	parse_echo(t_command *cmd);


int		count_cmds(const char *str, char c);
char	**ft_splitcmds(const char *str, char c);

#endif