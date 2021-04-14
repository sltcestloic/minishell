/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:42:19 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/14 15:55:13 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	echo(char *str, int option);
void	env(char **envp);

typedef struct s_envlst
{
	char	*name;
	char	*value;
	char	*next;
}	t_envlst;

#endif