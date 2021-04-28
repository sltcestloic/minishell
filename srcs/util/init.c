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

t_parser	init_parser(char *input)
{
	t_parser	ret;

	ret.backslash = 0;
	ret.d_quote = 0;
	ret.s_quote = 0;
	ret.parsed_input = malloc(ft_strlen(input) + 1);
	ft_bzero(ret.parsed_input, ft_strlen(input) + 1);
	ret.separators = malloc(sizeof(int) * (count_separators(input) + 1));
	ft_bzero(ret.parsed_input, count_separators(input) + 1);
	ret.has_cmd = 0;
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
