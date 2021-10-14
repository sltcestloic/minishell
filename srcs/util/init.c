#include "minishell.h"

int	count_separators(char *input)
{
	int	i;
	int	ret;

	i = 0;
	ret = 1;
	while (input[i])
	{
		if (input[i] == ';')
			ret++;
		i++;
	}
	return (ret);
}

t_parser	*init_parser()
{
	t_parser	*ret;

	ret = malloc(sizeof(t_parser));
	ret->d_quote = 0;
	ret->s_quote = 0;
	return (ret);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	ret->next = NULL;
	ret->in = NULL;
	ret->out = NULL;
	ret->value = NULL;
	return (ret);
}

t_index	init_index(void)
{
	t_index	ret;

	ret.i = 0;
	ret.j = 0;
	ret.k = 0;
	return (ret);
}