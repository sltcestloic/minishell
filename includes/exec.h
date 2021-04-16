/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:42:19 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/16 13:32:37 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_envlst
{
	char			*name;
	char			*value;
	struct s_envlst	*next;
}	t_envlst;

typedef struct	s_shell
{
	t_free		*to_free;
	t_envlst 	*env_var;
}	t_shell;

void		ft_exit(t_free *to_free);
void		echo(char *str, int option);
void		env(t_envlst *env_lst);
void		export(t_envlst *env_lst);
void		set_env(char **envp, t_shell *shell);
void		new_env_elem(char *str, t_shell *shell);
t_envlst	*copy_sorted_list(t_envlst *lst);

#endif