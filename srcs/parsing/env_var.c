#include "minishell.h"

char	*get_env_var(t_shell *shell, char *str)
{
	t_envlst	*lst;
	char		*ret;
	char		**split;
	char		*name;

	split = ft_split(str, ' ');
	name = ft_strtrim(&split[0][1], " \"'");
	lst = shell->env_var;
	ret = malloc(1);
	*ret = 0;
	while (lst)
	{
		if (ft_strcmp(lst->name, name) == 0)
		{
			free(ret);
			ret = ft_strdup(lst->value);
			break ;
		}
		lst = lst->next;
	}
	free_split(split);
	return (ret);
}

void	cat_var(t_parser *parser, char *var, char *input, t_index *indx)
{
	char	*swap;

	swap = malloc(ft_strlen(input) + ft_strlen(var));
	ft_strcpy(swap, parser->parsed_input);
	ft_strcat(swap, var);
	free(parser->parsed_input);
	parser->parsed_input = swap;
	indx->k = ft_strlen(parser->parsed_input);
	while (input[indx->i] && input[indx->i] != ' ')
		indx->i++;
	indx->i -= 2;
}
