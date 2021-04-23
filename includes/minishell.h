#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "exec.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>

void	display_prompt(t_shell *shell);

/*
** Utils
*/

int		ft_splitlen(char **split);

#endif