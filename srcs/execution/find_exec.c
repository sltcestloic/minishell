#include "minishell.h"

char **find_path(t_shell *shell)
{
	t_envlst *ptr;
	char **path;

	ptr = find_in_list("PATH", shell->env_var);
	path = ft_split(ptr->value, ':');
	return (path);
}
void	to_exec(t_shell *shell, char **function)
{
	int				i;
	char			**path;
	char			*test;
	struct stat 	*buf;
	char			*slash;

	buf = malloc(sizeof(struct stat));
	i = 0;
	path = find_path(shell);
	while (path[i])
	{

		slash = ft_strjoin(path[i], "/");
		test = ft_strjoin(slash, function[0]);
		if (!lstat(test, buf))
			break ;
		free(test);
		free(slash);
		test = 0;
		i++;
	}
	if (test)
		execve(test, &function[0], shell->envp);
}