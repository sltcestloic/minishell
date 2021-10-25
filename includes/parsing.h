#ifndef PARSING_H
# define PARSING_H
# include "exec.h"
# define REDIRECT_OUT >
# define REDIRECT_IN <
# define REDIRECT_APPEND >>
# define HEREDOC <<

typedef struct s_command
{
	char	**args;
	t_shell	*shell;
}				t_command;

typedef struct s_parser
{
	int		s_quote;
	int		d_quote;
	int		redirect;
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
char		*get_env_var(t_shell *shell, char *str, int quotes);
int			has_env_var(char *input);

/*
** Init
*/

t_parser	*init_parser();
t_index		init_index(void);
t_cmd		*init_cmd(void);

/*
** Commands parsing
*/

void		parse_echo(char **args);

t_cmd		*ft_splitcmds(const char *str, t_parser *parser);

/*
** Redirect
*/

int			is_redirect(char *str, int *i);
t_redirect	*redirect_last(t_redirect *redirect);
int			redirect_addback(t_redirect *redirect, int type);
void		init_redirect(t_cmd *cmd, int type);
void		set_file_name(t_redirect *redirect, char *input, int *i);

/*
** Debug
*/

void		print_cmd(t_cmd *cmd);

/*
** Substitute
*/

int			substitute(t_shell *shell, t_cmd *cmd);
char		*substitute_env_var(t_shell *shell, char *input, int var);

/*
** cmd
*/

void		add_new_cmd(t_cmd *cmd);
int			add_arg(t_cmd *cmd, char *input, t_shell *shell);

#endif