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
	char		*pwd;
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

#endif