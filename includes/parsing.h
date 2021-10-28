#ifndef PARSING_H
# define PARSING_H
# include "exec.h"
# define REDIRECT_OUT >
# define REDIRECT_IN <
# define REDIRECT_APPEND >>
# define HEREDOC <<

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

/*
** Main parsing
*/

void		parse_input(char *input, t_shell *shell);
int			count_args(char *input);

/*
** Environment variables
*/

char		*get_env_var(t_shell *shell, char *str, int quotes);
t_index		has_env_var(char *input, t_shell *shell);

/*
** Init
*/

t_parser	*init_parser(t_shell *shell);
t_index		init_index(void);
t_cmd		*init_cmd(void);
t_parser	init_parser_nml(void);

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
char		*substitute_env_var(t_shell *shell, char *input, int var, int quotes);
int			is_non_removable(t_parser *parser, char c);

/*
** cmd
*/

void		add_new_cmd(t_cmd *cmd);
int			add_arg(t_cmd *cmd, char *input, t_shell *shell);
void		cmd_bzero(t_cmd *cmd, int args);
void		quote_cmd(t_parser *parser, char c);
int			set_cmd_content(t_cmd *cmd, char *input, int *i, t_shell *shell);

/*
** Util
*/

int			is_sep(char c);
int			is_quote(char c);

#endif