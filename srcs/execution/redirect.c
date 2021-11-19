/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:18:05 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/19 14:37:55 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_out(t_redirect *redirect)
{
	int	fd;

	if (redirect->variation)
		fd = open(redirect->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redirect->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, 1) == -1 || close(fd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
}

void	redirect_in(t_redirect *redirect)
{
	int	fd;

	if (redirect->variation)
	{
		here_doc(redirect);
		return ;
	}
	fd = open(redirect->file_name, O_RDWR, 0644);
	if (fd == -1 || dup2(fd, 0) == -1 || close(fd) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
}

void	try_open(t_redirect *redirect)
{	
	int	fd;

	if (redirect->variation)
		return ;
	fd = open(redirect->file_name, O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redirect->file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
}

int	creat_trunc_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		g_last_exit = 1;
		exit(g_last_exit);
	}
	return (0);
}

void	redirect(t_cmd *cmd)
{
	while (cmd->in && cmd->in->next)
	{
		try_open(cmd->in);
		cmd->in = cmd->in->next;
	}
	if (cmd->in)
		redirect_in(cmd->in);
	while (cmd->out && cmd->out->next)
	{
		creat_trunc_file(cmd->out->file_name);
		cmd->out = cmd->out->next;
	}
	if (cmd->out)
		redirect_out(cmd->out);
}
