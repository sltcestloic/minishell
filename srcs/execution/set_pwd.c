#include "minishell.h"

void	go_home(t_shell *shell)
{
	t_envlst *ptr;

	ptr = find_in_list("HOME", shell->env_var);
	if (ptr)
		chdir(ptr->value);
	else
		write(2, "Minishell: cd: HOME not set\n", 23);
}

void	set_pwd(t_shell *shell)
{
	t_envlst	*ptr;

	ptr = shell->env_var;
	while(ptr && ft_strcmp(ptr->name, "PWD"))
	{
		ptr = ptr->next;
	}
	if (ptr)
		getcwd(ptr->value, 10000);
	getcwd(shell->pwd, 10000);
}

void	change_pwd(t_shell *shell, char *str)
{
	t_envlst	*ptr;

	if (str)
		chdir(str);
	else
		go_home(shell);
	ptr = shell->env_var;
	while(ptr && ft_strcmp(ptr->name, "PWD"))
	{
		ptr = ptr->next;
	}
	if (ptr)
		getcwd(ptr->value, 10000);
	getcwd(shell->pwd, 10000);
}

void	pwd(t_shell *shell)
{
	ft_putstr_fd(shell->pwd, 1);
	write(1, "\n", 1);
}