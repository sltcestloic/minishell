/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 14:54:38 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/19 14:55:47 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <termios.h>

extern int	g_last_exit;

typedef struct s_redirect
{
	char				*file_name;
	struct s_redirect	*next;
	int					variation;
	int					quotes;
}	t_redirect;

typedef struct s_fdsys
{
	int		fd_in;
	int		fd_out;
}	t_fdsys;

typedef struct s_envlst
{
	char			*name;
	char			*value;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_shell
{
	t_fdsys			fdsys;
	t_free			*to_free;
	t_envlst		*env_var;
	char			*pwd;
	char			**envp;
	int				to_close;
	struct termios	old;
	struct termios	new;
}				t_shell;

typedef struct s_cmd
{
	char			**value;
	struct s_cmd	*next;
	t_redirect		*in;
	t_redirect		*out;
	int				quotes;
	t_shell			*shell;
}	t_cmd;

void		ft_exit(t_free *to_free);

void		echo(char **str);
void		env(t_envlst *env_lst);
void		export(t_envlst *env_lst, t_shell *shell);
void		update_env_value(t_shell *shell, char **arg);
void		new_env_elem(char *str, t_shell *shell);
void		remove_env_elem(char **arg, t_shell *shell);
void		pwd(t_shell *shell);
void		exit_cmd(t_shell *shell, char **arg, int is_pipe);

void		set_pwd(t_shell *shell);
void		change_pwd(t_shell *shell, char *str);
void		set_env(char **envp, t_shell *shell);
int			init_fd(t_shell *shell);

t_envlst	*copy_sorted_list(t_envlst *lst, t_shell *shell);
t_envlst	*find_in_list(char *str, t_envlst *ptr);
t_envlst	*last_lst_elem(t_envlst *lst);
int			size_list(t_envlst *lst);

void		to_exec(t_shell *shell, char **function);
void		redirect(t_cmd *cmd);
void		cmd_parse(t_cmd *cmd, t_shell *shell);
char		**lst_to_str(t_shell *shell);

int			open_dup_redirect(t_cmd *cmd, int fd_stream);
int			open_creat(char *file_path);
void		here_doc(t_redirect *heredoc);
int			do_heredoc(t_cmd *cmd);
int			parse_here_doc(t_redirect *heredoc);

void		unset_term(t_shell *shell);
void		if_sigint(int sig);
void		signal_reset(int osef);
int			signal_handle(int pid);

char		**find_path(t_shell *shell);
char		*copy_name(char *str, t_shell *shell);
char		*copy_value(char *str, t_shell *shell);
void		print_error(char *cmd, char *msg, int exit_value);

int			is_built_in(t_cmd *cmd);
int			redirect_to_built_in(t_cmd *cmd, t_shell *shell);
void		check_built_in(char **func, t_shell *shell);

#endif