#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "parsing.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/param.h>
# include "exec.h"

void	display_prompt(t_shell *shell);

/*
** Utils
*/

int		ft_splitlen(char **split);
void	cmd_addback(t_cmd *cmd, t_cmd *add);
void	cmd_free(t_cmd *cmd);
int		cmd_last_type(t_cmd *cmd);
t_cmd	*cmd_last(t_cmd *cmd);
void	print_cmd(t_cmd *cmd);
void	set_term(t_shell *shell);
void	unset_term(t_shell *shell);

#endif