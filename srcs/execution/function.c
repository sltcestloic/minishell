#include "minishell.h"

void	echo(char **str)
{
	if (str[1] && ft_strcmp(str[1], "-n"))
	{
		if (str[2])
			write(1, str, ft_strlen(str[2]));
		return ;
	}
	else if (str[1])
		write(1, str, ft_strlen(str[1]));
	write(1, "\n", 1);
}

void	env(t_envlst *lst)
{
	if (lst)
	{
		while (lst)
		{
			if (lst->name)
				ft_putstr_fd(lst->name, 1);
			if (lst->value)
			{
				write(1, "=", 1);
				ft_putstr_fd(lst->value, 1);
			}
			write(1, "\n", 1);
			lst = lst->next;
		}
	}
}

void	export(t_envlst *lst)
{
	t_envlst	*sorted;

	if (lst)
	{
		sorted = copy_sorted_list(lst);
		while (sorted)
		{
			if (sorted->value)
			{
				write(1, "declare -x ", 11);
				ft_putstr_fd(sorted->name, 1);
				write(1, "=\"", 2);
				ft_putstr_fd(sorted->value, 1);
				write(1, "\"", 1);
				write(1, "\n", 1);
			}
			sorted = sorted->next;
		}
	}
}

void	ft_exit(t_free *to_free)
{
	ft_free(to_free);
	write(1, "exit\n", 5);
	exit(0);
}
