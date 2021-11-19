/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:35:58 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/19 13:37:00 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	exec_it(char *test, char **function, t_shell *shell)
{
	if (!function[0][0])
		print_error("\0", ": command not found", 127);
	else if (execve(test, function, lst_to_str(shell)))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(function[0]);
		last_exit = 127;
		exit (127);
	}
}

int	is_abs_path(char *str, t_shell *shell)
{
	int			i;
	struct stat	buff;

	i = 0;
	while (str[i] && str[i] != '/')
		i++;
	if (!str[i] && str[0] != '.' && find_in_list("PATH", shell->env_var))
		return (0);
	if (stat(str, &buff) == -1)
		print_error(str, ": No such file or directory", 127);
	if (S_ISDIR(buff.st_mode))
		print_error(str, ": is a directory", 126);
	i = open(str, O_RDONLY);
	if (i == -1 || access(str, X_OK) != 0)
	{
		if (i != -1)
			close (i);
		print_error(str, ": Permision denied", 126);
	}
	close(i);
	return (1);
}

int	check_access(char *str, char **denied)
{
	int ret;

	ret = open(str, O_RDONLY);
	if (ret == -1)
		return (-2);
	ret = access(str, X_OK);
	if (ret == -1 && !*denied)
	{
		*denied = str;
		return (-1);
	}
	else if (ret == -1 && *denied)
		return (-1);
	return (0);
}

char	*make_path(char **path, char **function, t_shell *shell)
{
	char	*test;
	char	*slash;
	char	*denied;
	int		i;
	int		ret;

	i = (ret = 0);
	denied = NULL;
	while (path[i])
	{
		slash = ft_strjoin(path[i], "/", shell->to_free);
		if (!slash)
			ft_malloc_error(shell->to_free);
		test = ft_strjoin(slash, function[0], shell->to_free);
		if (!test)
			ft_malloc_error(shell->to_free);
		ret = check_access(test, &denied);
		if (ret == 0)
			return (test);
		i++;
	}
	if (ret == -1)
		print_error(denied, ": Permision denied", 126);
	return (NULL);
}

void	check_built_in(char **func, t_shell *shell)
{
	if (!ft_strcmp(func[0], "echo"))
		echo(func);
	else if (!ft_strcmp(func[0], "env"))
		env(shell->env_var);
	else if (!ft_strcmp(func[0], "export"))
	{
		if (!func[1])
			export(shell->env_var, shell);
		else if (func[1])
			new_env_elem(func[1], shell);
	}
	else if (!ft_strcmp(func[0], "unset"))
		remove_env_elem(func, shell);
	else if (!ft_strcmp(func[0], "exit"))
		exit_cmd(shell, func, 1);
	else if (!ft_strcmp(func[0], "cd"))
		change_pwd(shell, func[1]);
	else if (!ft_strcmp(func[0], "pwd"))
		pwd(shell);
	else
		return ;
	exit(last_exit = 0);
}

void	to_exec(t_shell *shell, char **function)
{
	char	**path;
	char	*test;

	check_built_in(function, shell);
	path = find_path(shell);
	test = NULL;
	if (is_abs_path(function[0], shell))
		test = function[0];
	else if (path && path[0][0])
		test = make_path(path, function, shell);
	else
		print_error(function[0], ": No such file or directory", 127);
	if (test)
		exec_it(test, &function[0], shell);
	else
		print_error(function[0], ": command not found", 127);
}
