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
    int i;
    int j;
    t_list   *chain;
    t_list   *tmp;

    i = 0;
    chain = NULL;
    while (av[1][i])
    {
        while (av[1][i] == ' ')
            i++;
        if (av[1][i] == '\0')
            break ;
        tmp = (t_list *)malloc(sizeof(t_list));
        if (!tmp)
            free(tmp);
        tmp->content = (t_lex *)malloc(sizeof(t_lex));
        if (!tmp->content)
        {
            free(tmp->content);
            free(tmp);
        }
        if (av[1][i] == '|' && av[1][i + 1] == '|')
        {
            ((t_lex *) tmp->content)->type = "OR";
            ((t_lex *) tmp->content)->str = "||";
            i += 2;
        }
        else if (av[1][i] == '&' && av[1][i + 1] == '&')
        {
            ((t_lex *) tmp->content)->type = "AND";
            ((t_lex *) tmp->content)->str = "&&";
            i += 2;
        }
        else if (av[1][i] == '(')
        {
            ((t_lex *) tmp->content)->type = "LPAREN";
            ((t_lex *) tmp->content)->str = "(";
            i++;
        }
        else if (av[1][i] == ')')
        {
            ((t_lex *) tmp->content)->type = "RPAREN";
            ((t_lex *) tmp->content)->str = ")";
            i++;
        }
        else if (av[1][i] == '|')
        {
            ((t_lex *) tmp->content)->type = "PIPE";
            ((t_lex *) tmp->content)->str = "|";
            i++;
        }
        else if (av[1][i] == '<' && av[1][i + 1] == '<')
        {
            i += 2;
            ((t_lex *) tmp->content)->type = "LLESS";
            j = 0;
            while(av[1][i + j] != ' ' && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else if (av[1][i] == '>' && av[1][i + 1] == '>')
        {
            i += 2;
            ((t_lex *) tmp->content)->type = "GGREAT";
            j = 0;
            while(av[1][i + j] != ' ' && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else if (av[1][i] == '<')
        {
            i++;
            ((t_lex *) tmp->content)->type = "LESS";
            j = 0;
            while(av[1][i + j] != ' ' && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else if (av[1][i] == '>')
        {
            i++;
            ((t_lex *) tmp->content)->type = "GREAT";
            j = 0;
            while(av[1][i + j] != ' ' && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else
        {
            ((t_lex *) tmp->content)->type = "CMD";
            j = 0;
            while(av[1][i + j] != ' ' && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        ft_lstadd_back(&chain, tmp);
        printf("%s\n", ((t_lex *) tmp->content)->str);
    }
    tmp = chain;
    while (tmp)
    {
        printf("%s\n", ((t_lex *) tmp->content)->type);
        tmp = tmp->next;
    }
    return (0);
}
