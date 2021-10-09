#include "minishell.h"

char	**find_path(t_shell *shell)
{
	t_envlst	*ptr;
	char		**path;

	ptr = find_in_list("PATH", shell->env_var);
	path = 0;
	if (ptr)
		path = ft_split(ptr->value, ':');
	return (path);
}

static inline void	exec_it(char *test, char **function, char **envp)
{
	if (execve(test, function, envp))
	{
		write(2, "Minishell: ", 11);
		ft_putstr_fd(test, 2);
		write(2, ": No such file or directory\n", 28);
		free(test);
		exit(-1);
	}
}

char	*make_path(char **path, char **function)
{
	char			*test;
	struct stat		*buf;
	char			*slash;
	int				i;
	int ret = 0;

	i = 0;
	buf = malloc(sizeof(struct stat));
	while (function[0][i] && function[0][i] != '/')
		i++;
	if (function[0][i])
		return (ft_strdup(function[0]));
	else
		i = 0;
	while (path[i])
	{
		slash = ft_strjoin(path[i], "/");
		test = ft_strjoin(slash, function[0]);
		free(slash);
		if ((ret = access(test, X_OK)) == 0)
			return (test);
		free(test);
		test = NULL;
		i++;
	}
	return (test);
}

void	to_exec(t_shell *shell, char **function)
{
	char			**path;
	char			*test;

	path = find_path(shell);
	test = NULL;
	if (path)
		test = make_path(path, function);
	if (test)
		exec_it(test, &function[0], shell->envp);
	else
		ft_putstr_fd("Minishell: command not found\n", 2);
	exit(-1);
}
