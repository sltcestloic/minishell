#include "minishell.h"

void	echo(char **str)
{
	int i;
	int j;
	int option;

	option = 0;
	i = 1;
	while (str[i] && str[i][0] == '-')
	{
		j = 1;
		while (str[i][j] == 'n')
			j++;
		if (!str[i][j])
		{
			option = 1;
			i++;
		}
		else
			break ;
	}
	while (str[i++])
		if (printf("%s", str[i - 1]) && str[i])
			printf(" ");
	if (!option)
		printf("\n");
}

void	env(t_envlst *lst)
{
	while (lst)
	{
		if (lst->value)
		{
			if (lst->name)
			{
				ft_putstr_fd(lst->name, 1);
				write(1, "=", 1);
				ft_putstr_fd(lst->value, 1);
				write(1, "\n", 1);
			}
		}
		lst = lst->next;
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
			if (sorted->name)
			{
				printf("declare -x %s", sorted->name);
				if (sorted->value)
					printf("=\"%s\"", sorted->value);
				printf("\n");
				sorted = sorted->next;
			}
		}
	}
}

void	exit_cmd(t_shell *shell, char **arg)
{
	int ret;
	char *save;

	ret = 0;
	write(1, "exit\n", 5);
	if (arg[1] && arg[2])
	{
		printf("minishell: exit: too many arguments\n");
		exit(255);
		return ;
	}
	if (arg[1])
	{
		ret = ft_atoi(arg[1]);
		save = ft_itoa(ret);
		if (ft_strcmp(save, arg[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", arg[1]);
			exit(255);
			return ;
		}
	}
	// ft_free(shell->to_free);
	(void) shell->to_free;
	exit((unsigned char)ret);
}

void	ft_exit(t_free *to_free)
{
	ft_free(to_free);
	exit(0);
}
