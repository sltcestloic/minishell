#ifndef EXEC_H
# define EXEC_H

typedef struct s_cmd
{
	int				type;
	char			**value;
	struct s_cmd	*next;
}	t_cmd;

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

typedef struct	s_shell
{
	t_fdsys		fdsys;
	t_free		*to_free;
	t_envlst 	*env_var;
	char		*pwd;
	char		**envp;
}	t_shell;

void		ft_exit(t_free *to_free);
void		echo(char *str, int option);
void		env(t_envlst *env_lst);
void		export(t_envlst *env_lst);
void		set_env(char **envp, t_shell *shell);
void		new_env_elem(char *str, t_shell *shell);
void		remove_env_elem(char *name, t_shell *shell);
t_envlst	*find_in_list(char *str, t_envlst *ptr);
t_envlst	*copy_sorted_list(t_envlst *lst);
void		set_pwd(t_shell *shell);
void		change_pwd(t_shell *shell, char *str);
void		pwd(t_shell *shell);
void		to_exec(t_shell *shell, char **function);
int			redirect(t_cmd *cmd);
int			open_dup_redirect(t_cmd *cmd, int fd_stream);
int			open_creat(char *file_path);

#endif