#include "minishell.h"

int main(int ac, char **av)
{
    // char    **tokens;
    // int     i;
    // int     j;

    // tokens = (char **)malloc(sizeof(char *) * (ac - 1));
    // i = 0;
    // while (++i < ac)
    // {
    //     j = 0;
    //     if (av[i][j] == '<' && av[i][j + 1] == '<')
    //         tokens[i - 1] = "LESSLESS";
    //     else if (av[i][j] == '>' && av[i][j + 1] == '>')
    //         tokens[i - 1] = "GREATGREAT";
    //     else if (av[i][j] == '<')
    //         tokens[i - 1] = "LESS";
    //     else if (av[i][j] == '>')
    //         tokens[i - 1] = "GREAT";
    //     else if (av[i][j] == '|')
    //         tokens[i - 1] = "PIPE";
    //     else
    //         tokens[i - 1] = av[i];
    // }
    // while (tokens[j])
    // {
    //     printf("%s\n", tokens[j]);
    //     j++;
    // }

    (void) ac;
    char **str = ft_split(av[1], ' ');
    int i = -1;
    while (str[++i])
        printf("%s\n", str[i]);
    return (0);
}