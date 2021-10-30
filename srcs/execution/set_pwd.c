#include "minishell.h"

void	go_home(t_shell *shell)
{
	t_envlst	*ptr;

	ptr = find_in_list("HOME", shell->env_var);
	if (ptr)
		chdir(ptr->value);
	else
		write(2, "minishell: cd: HOME not set\n", 28);
}

void	set_pwd(t_shell *shell)
{
	t_envlst	*ptr;
	t_envlst	*oldptr;

	ptr = shell->env_var;
	oldptr = shell->env_var;
	while (oldptr && ft_strcmp(oldptr->name, "OLDPWD"))
		oldptr = oldptr->next;
	if (oldptr)
		oldptr->value = NULL;
	while (ptr && ft_strcmp(ptr->name, "PWD"))
		ptr = ptr->next;
	if (ptr)
		getcwd(ptr->value, 10000);
	getcwd(shell->pwd, 10000);
}

void	change_pwd(t_shell *shell, char *str)
{
	t_envlst	*ptr;
	t_envlst	*oldptr;

	if (str)
	{
		if (chdir(str) == -1 && write(2, "minishell: cd: ", 15))
			perror(str);
	}
	else
		go_home(shell);
	ptr = shell->env_var;
	while (ptr && ft_strcmp(ptr->name, "PWD"))
		ptr = ptr->next;
	oldptr = shell->env_var;
	while (oldptr && ft_strcmp(oldptr->name, "OLDPWD"))
		oldptr = oldptr->next;
	if (oldptr)
		oldptr->value = ptr->value;
	if (ptr)
	{
		ptr->value = ft_malloc(MAXPATHLEN, &shell->to_free);
		getcwd(ptr->value, MAXPATHLEN);
	}
	getcwd(shell->pwd, MAXPATHLEN);
}

void	pwd(t_shell *shell)
{
	printf("%s\n", shell->pwd);
}
