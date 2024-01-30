#include "minishell.h"

int main(int ac, char **av)
{
    t_lex   *a;
    t_lex   *chain;
    char    **tokens;
    int     i;
    int     j;

    tokens = (char **)malloc(sizeof(char *) * (ac - 1));
    i = 0;
    while (++i < ac)
    {
        j = 0;
        if (av[i][j] == '<' && av[i][j + 1] == '<')
            tokens[i - 1] = "LESSLESS";
        else if (av[i][j] == '>' && av[i][j + 1] == '>')
            tokens[i - 1] = "GREATGREAT";
        else if (av[i][j] == '<')
            tokens[i - 1] = "LESS";
        else if (av[i][j] == '>')
            tokens[i - 1] = "GREAT";
        else if (av[i][j] == '|')
            tokens[i - 1] = "PIPE";
        
    }
}