/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:43:59 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/23 13:09:59 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **str)
{
	int	i;
	int	j;
	int	option;

	option = 0;
	i = 1;
	g_last_exit = 0;
	while (str[i] && (str[i][0] == '-' && str[i][1]))
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
	g_last_exit = 0;
	while (lst)
	{
		if (lst->value)
		{
			if (lst->name)
				printf("%s=%s\n", lst->name, lst->value);
		}
		lst = lst->next;
	}
}

void	export(t_envlst *lst, t_shell *shell)
{
	t_envlst	*sorted;

	g_last_exit = 0;
	if (lst)
	{
		sorted = copy_sorted_list(lst, shell);
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

static int	ft_atoi_exit(char *arg, unsigned long *ret)
{
	int	i;
	int	nega;

	nega = 1;
	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '-' && ++i)
		nega = -1;
	else if (arg[i] == '+' && ++i)
		nega++;
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		*ret = *ret * 10 + (arg[i] - '0');
		if ((*ret > LONG_MAX && nega != -1) || *ret > (unsigned long)LONG_MIN)
			return (-1);
		i++;
	}
	while (arg[i] == ' ')
		i++;
	if (arg[i] || (nega != 1 && *ret == 0))
		return (-1);
	*ret *= nega;
	return (0);
}

void	exit_cmd(t_shell *shell, char **arg, int is_pipe)
{
	unsigned long	ret;

	ret = g_last_exit;
	if (!is_pipe)
	{
		unset_term(shell);
		write(2, "exit\n", 5);
	}
	if (!arg)
		exit(g_last_exit);
	if (arg[1])
	{
		ret = 0;
		if (ft_atoi_exit(arg[1], &ret) == -1)
			print_error(arg[1], ": numeric argument required", 255);
		else if (arg[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_last_exit = 1;
			return ;
		}
	}
	unset_term(shell);
	ft_free(shell->to_free);
	exit((unsigned char)ret);
}
