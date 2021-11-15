#include "minishell.h"

void     if_sigint(int osef)
{
    (void)osef;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void     if_sigheredoc(int sig)
{
    (void) sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}