#include "minishell.h"

void	echo(char **str)
{
	if (str[1] && !ft_strcmp(str[1], "-n"))
	{
		if (str[2])
			printf("%s", str[2]);
		return ;
	}
	else if (str[2])
		printf("%s", str[1]);
	printf("\n");
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

void	exit_cmd(t_shell *shell, char **arg)
{
	int ret;
	char *save;

	ret = 0;
	if (arg[2])
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	if (arg[1])
	{
		ret = ft_atoi(arg[1]);
		save = ft_itoa(ret);
		if (ft_strcmp(save, arg[1]))
		{
			free(save);
			printf("minishell: exit: %s: numeric argument required\n", arg[1]);
			return ;
		}
		free(save);
	}
	ft_free(shell->to_free);
	write(1, "exit\n", 5);
	exit(ret);
}

void	ft_exit(t_free *to_free)
{
	ft_free(to_free);
	exit(0);
}
