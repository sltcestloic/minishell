/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:14:12 by owlly             #+#    #+#             */
/*   Updated: 2021/11/26 17:00:17 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *msg, int exit_value)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(g_last_exit = exit_value);
}

int	dup_close(int new_fd, int old_fd)
{
	if (dup2(new_fd, old_fd) == -1)
	{
		perror("minishell :");
		return (-1);
	}
	close(new_fd);
	return (0);
}

int	err_proc(int fd1, int fd2, int fd3)
{
	close(fd1);
	close(fd2);
	close(fd3);
	perror("minishell :");
	return (1);
}

int	err_pipe(int fd)
{
	if (fd)
		close(fd);
	perror("minishell :");
	return (1);
}
