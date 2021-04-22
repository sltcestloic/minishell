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
	DIR				*current_dir;
	struct dirent	*dir;
	int				i;
	char			**path;
	
	i = 0;
	path = find_path(shell);
	while (path[i])
	{
		current_dir = opendir(path[i]);
		dir = readdir(current_dir);
		while (current_dir && dir)
		{
			if (ft_strcmp(dir->d_name, function[0]) == 0)
				break;
			dir = readdir(current_dir);
		}
		i++;
	}
	execve(ft_strjoin(path[i], function[0]), &function[1], shell->envp);
}