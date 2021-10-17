#include "minishell.h"

inline static char	*copy_name(char *str, t_shell *shell)
{
	register int	i;
	char			*ptr;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	ptr = ft_malloc(i + 1, &shell->to_free);
	if (!ptr)
		return (ptr);
	i = -1;
	while (str[++i] != '=' && str[i])
		ptr[i] = str[i];
	ptr[i] = 0;
	return (ptr);
}

inline static char	*copy_value(char *str, t_shell *shell)
{
	register int	i;
	register int	j;
	char			*ptr;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
		i++;
	while (str[i + j])
		j++;
	if (j == 0)
		return (0);
	i++;
	ptr = ft_malloc(j + 1, &shell->to_free);
	if (ptr)
	{
		j = 0;
		while (str[i + j])
		{
			ptr[j] = str[i + j];
			j++;
		}
		ptr[j] = 0;
	}
	return (ptr);
}

t_envlst	*find_in_list(char *str, t_envlst *ptr)
{
	while (ptr && ft_strcmp(ptr->name, str))
		ptr = ptr->next;
	return (ptr);
}

void	new_env_elem(char *str, t_shell *shell)
{
	t_envlst	*ptr;
	t_envlst	*save;

	save = shell->env_var;
	if (save)
	{
		while (save->next)
			save = save->next;
		ptr = (t_envlst *)ft_malloc(sizeof(t_envlst), &(shell->to_free));
		save->next = ptr;
	}
	else
	{
		ptr = (t_envlst *)ft_malloc(sizeof(t_envlst), &(shell->to_free));
		shell->env_var = ptr;
	}
	if (ptr)
	{
		ptr->name = copy_name(str, shell);
		ptr->value = copy_value(str, shell);
		ptr->next = 0;
	}
	if (!ptr || !ptr->name)
		ft_exit(shell->to_free);
}

void	remove_env_elem(char *name, t_shell *shell)
{
	t_envlst	*ptr;

	ptr = shell->env_var;
	while (ptr->next && ft_strcmp(ptr->next->name, name))
	{
		ptr = ptr->next;
	}
	if (ptr->next)
		ptr->next = ptr->next->next;
}

void	set_env(char **envp, t_shell *shell)
{
	register int	i;

	i = 0;
	while (envp[i])
	{
		new_env_elem(envp[i], shell);
		i++;
	}
}
