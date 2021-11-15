#include "minishell.h"

inline static char	*copy_name(char *str, t_shell *shell)
{
	register int	i;
	char			*ptr;

	i = 0;
	while ((str[i] != '+' || str[i] != '=') && str[i])
		i++;
	ptr = ft_malloc(i + 1, &shell->to_free);
	if (!ptr)
		return (ptr);
	i = -1;
	while (str[++i] != '=' && str[i] != '+' && str[i])
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
		return (NULL);
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

static int	is_equal_concatenate(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
			{
				return (2);
			}
			else
				return (-1);
		}
		else if (str[i] == '=')
		{
			return (1);
		}
		else
			i++;
	}
	return (0);
}

void	update_env_value(t_shell *shell, char **arg)
{
	t_envlst	*item;
	t_free		*o;
	int			i;

	i = 1;
	o = shell->to_free;
	while (arg[i])
	{
		item = find_in_list(copy_name(arg[i], shell), shell->env_var);
		if (is_equal_concatenate(arg[i]) == -1)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			last_exit = 1;
		}
		else if (item && is_equal_concatenate(arg[i]) == 1)
			item->value = copy_value(arg[i], shell);
		else if (item && is_equal_concatenate(arg[i]) == 2)
			item->value = ft_strjoin(item->value, copy_value(arg[i], shell), o);
		else if (!item)
			new_env_elem(arg[i], shell);
		i++;
	}
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

	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '=' || str[0] == '+')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		last_exit = 1;
		return ;
	}
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

void	remove_env_elem(char **arg, t_shell *shell)
{
	t_envlst	*ptr;
	int			i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i][0] >= '0' && arg[i][0] <= '9') || arg[i][0] == '='\
		|| arg[i][0] == '+' || arg[i][0] == '-')
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			last_exit = 1;
		}
		ptr = shell->env_var;
		if (!ptr)
			return ;
		while (ptr && ft_strcmp(ptr->name, arg[i]))
		{
			ptr = ptr->next;
		}
		if ()
		if (ptr->next)
			ptr->next = ptr->next->next;
		i++;
	}
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
