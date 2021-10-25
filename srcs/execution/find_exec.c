#include "minishell.h"


char	**find_path(t_shell *shell)
{
	t_envlst	*ptr;
	char		**path;

	ptr = find_in_list("PATH", shell->env_var);
	path = 0;
	if (ptr)
	{
		path = ft_split(ptr->value, ':', shell->to_free);
		if(!path)
			ft_malloc_error(shell->to_free);
	}
	return (path);
}

static inline void	exec_it(char *test, char **function, t_shell *shell)
{
	if (execve(test, function, lst_to_str(shell)))
	{
		write(2, "minishell: ", 11);
		ft_putstr_fd(test, 2);
		write(2, ": No such file or directory\n", 28);
		exit(-1);
	}
}

int		find_slash(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '/')
		i++;
	if (str[i])
		return (1);
	return (0);
}

char	*make_path(char **path, char **function, t_shell *shell)
{
	char			*test;
	char			*slash;
	int				i;
	int ret = 0;

	i = 0;
	if (find_slash(function[0]))
		return (function[0]);
	while (path[i])
	{
		slash = ft_strjoin(path[i], "/", shell->to_free);
		if(!slash)
			ft_malloc_error(shell->to_free);
		test = ft_strjoin(slash, function[0], shell->to_free);
		if(!test)
			ft_malloc_error(shell->to_free);
		if ((ret = access(test, X_OK)) == 0)
			return (test);
		i++;
	}
	return (NULL);
}

int	check_built_in(char **func, t_shell *shell)
{
	if (!ft_strcmp(func[0], "echo"))
		echo(func);
	else if (!ft_strcmp(func[0], "env"))
		env(shell->env_var);
	else if (!ft_strcmp(func[0], "export"))
	{
		if (!func[1])
			export(shell->env_var);
		else if(func[1])
			new_env_elem(func[1], shell);
	}
	else if (!ft_strcmp(func[0], "unset"))
		remove_env_elem(func[1], shell);
	else if (!ft_strcmp(func[0], "exit"))
		ft_exit(shell->to_free);
	else if (!ft_strcmp(func[0], "cd"))
		change_pwd(shell, func[1]);
	else if (!ft_strcmp(func[0], "pwd"))
		pwd(shell);
	else
		return (0);
	return (1);
}

void	to_exec(t_shell *shell, char **function)
{
	char			**path;
	char			*test;

	if(check_built_in(function, shell))
		exit(0);
	path = find_path(shell);
	test = NULL;
	if (path)
		test = make_path(path, function, shell);
	if (test)
		exec_it(test, &function[0], shell);
	else
		ft_putstr_fd("Minishell: command not found\n", 2);
	exit(-1);
}
