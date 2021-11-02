#include "minishell.h"

typedef	struct s_test
{
	char	*name;
	char	*command;
	char	***values;
}				t_test;


void	load_tests(t_list **tests) {
	FILE	*file;
    char	*line = NULL;
    size_t	len = 0;
    ssize_t read;
	t_list	*list = *tests;
	t_list	*newlist;

	file = fopen("./tests", "r");
    if (file == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, file)) != -1) {

		if (line[0] == '#') continue;

		char	**split = ft_split(line, ';', NULL);

		for (int i = 0; i < 4; i++)
			printf("%s\n", split[i]);

		t_test	*test = malloc(sizeof(t_test));
		test->name = strdup(split[0]);
		test->command = strdup(split[1]);

		char	**values = ft_split(split[2], ',', NULL);

		test->values = malloc(sizeof(char **) * (ft_splitlen(values) + 1));

		for (int i = 0; i < ft_splitlen(values); i++) {
			test->values[i] = malloc(sizeof(char *) * (ft_splitlen(values) + 1));
			test->values[i + 1] = 0;
		}

		for (int i = 0; i < ft_splitlen(values); i++) {
			char	**values_split = ft_split(values[i], ':', NULL);
			test->values[atoi(values_split[0])][atoi(values_split[1])] = strdup(values_split[2]);
			test->values[atoi(values_split[0])][atoi(values_split[1]) + 1] = 0;
		}

        if (!list)
			list = ft_lstnew(test);
		else {
			newlist = ft_lstnew(test);
			ft_lstadd_back(tests, newlist);
		}
    }

	*tests = list;
    fclose(file);
    if (line)
        free(line);
}

int	unit_test(t_shell *shell) {
	t_list	*tests = NULL;
	t_test	*test = NULL;
	t_cmd	*cmd;
	int		success = 0;

	load_tests(&tests);
	while (tests) {

		test = tests->content;
		printf("command: %s\n", test->command);
		cmd = parse_input(test->command, shell);

		int	i = 0;
		while (cmd) {
			for (int j = 0; cmd->value[j]; j++) {
				if (!test->values[i][j] || strcmp(test->values[i][j], cmd->value[j]) != 0) {
					success = 0;
					break;
				}
			}
			i++;
			cmd = cmd->next;
		}
		tests = tests->next;
	}
	return 0;
}