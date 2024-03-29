#include "minishell.h"

int check_cmd(char *str, char *cmd)
{
    int i;

    i = 0;
    while (str[i] || cmd[i])
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            if (!(cmd[i] == str[i] + 'a' - 'A' || cmd[i] == str[i]))
                return (0);
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            if (!(cmd[i] == str[i] + 'A' - 'a' || cmd[i] == str[i]))
                return (0);
        }
        else
        {
            if (cmd[i] != str[i])
                return (0);
        }
        i++;
    }
    return(1);
}

t_list *initenvp(char **envp)
{
    t_list  *env;
    t_list  *tmp;
    int     i;
    int     j;

    i = -1;
    while (envp[++i])
    {
        j = -1;
        while (envp[i][++j] != '=');
        tmp = (t_list *)malloc(sizeof(t_list));
        if (!tmp)
            return (NULL);
        tmp->content = (t_lex *)malloc(sizeof(t_lex));
        if (!tmp->content)
        {
            //free(env)
            free(tmp->content);
            free(tmp);
        }
        ((t_lex *) tmp->content)->type = ft_substr((const char *)envp[i], 0, j);
        ((t_lex *) tmp->content)->str = ft_strdup(&envp[i][j + 1]);
        printf("%s=%s\n", ((t_lex *) tmp->content)->type, ((t_lex *) tmp->content)->str);
        ft_lstadd_back(&env, tmp);
    }
    return (env);
}

int find_special(char c)
{
    if (c == '|' || c == '&' || c == '<' 
        || c == '>' || c == '(' || c == ')'
        || c == ' ')
        return (1);
    return (0);
}

int main(int ac, char **av, char **envp)
{
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
            while(av[1][i + j] == ' ')
                j++;
            i = i + j;
            j = 0;
            while(!find_special(av[1][i + j]) && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else if (av[1][i] == '>' && av[1][i + 1] == '>')
        {
            i += 2;
            ((t_lex *) tmp->content)->type = "GGREAT";
            j = 0;
            while(av[1][i + j] == ' ')
                j++;
            i = i + j;
            j = 0;
            while(!find_special(av[1][i + j]) && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else if (av[1][i] == '<')
        {
            i++;
            ((t_lex *) tmp->content)->type = "LESS";
            j = 0;
            while(av[1][i + j] == ' ')
                j++;
            i = i + j;
            j = 0;
            while(!find_special(av[1][i + j]) && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else if (av[1][i] == '>')
        {
            i++;
            ((t_lex *) tmp->content)->type = "GREAT";
            j = 0;
            while(av[1][i + j] == ' ')
                j++;
            i = i + j;
            j = 0;
            while(!find_special(av[1][i + j]) && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        else
        {
            ((t_lex *) tmp->content)->type = "CMD";
            j = 0;
            while(!find_special(av[1][i + j]) && av[1][i + j] != '\0')
                j++;
            ((t_lex *) tmp->content)->str = ft_substr(av[1], i, j);
            i += j;
        }
        //conditional checking on NULL infile/outfile
        ft_lstadd_back(&chain, tmp);
        printf("%s\n", ((t_lex *) tmp->content)->str);
    }

    // data structure of parsing
    // table -> table when diff pipe & duplicate redirection appears
    // each table has 1 infile, 1 outfile, 1 cmd_lst
    // cmd_lst -> cmd_lst when there is pipe, cmd_list is all cmds within that pipe
    // in each cmd_lst, there should be another linked list / array to link all cmds

    // tmp = chain;
    // t_table *cmd_table;
    // cmd_table = (t_table *) malloc(sizeof(t_table));
    // cmd_table->infile = NULL;
    // cmd_table->outfile = NULL;
    // cmd_table->append = -1;
    // cmd_table->cmd_lst = NULL;
    // t_list *table;
    // table = (t_list *) malloc(sizeof(t_list));
    // table->content = (void *) cmd_table;
    // table->next = NULL;
    // while (tmp)
    // {
    //     if (ft_strncmp(((t_lex *) tmp->content)->type, "CMD", 3) == 0)
    //     {
    //         t_list *tmp_cmd_lst;
    //         t_list *cmd;
    //         t_list *tmp_cmd;
    //         tmp_cmd_lst = (t_list *) malloc(sizeof(t_list));
    //         tmp_cmd_lst->content = (void *)cmd;
    //         tmp_cmd_lst->next = NULL;
    //         cmd = tmp_cmd;
    //         tmp_cmd = (t_list *) malloc(sizeof(t_list));
    //         tmp_cmd->content = (void *) ft_strdup(((t_lex *) tmp->content)->str);
    //         tmp_cmd->next = NULL;
    //     }
    //     // else if (ft_strncmp(((t_lex *) tmp->content)->type, "PIPE", 4) == 0)
    // }
    // while (tmp)
    // {
    //     printf("%s\n", ((t_lex *) tmp->content)->type);
    //     tmp = tmp->next;
    // }
    (void) envp;
    // printf("%d\n", check_cmd(av[1], "echo"));
    // printf("%s\n", ft_strchr(envp[0], '='));
    // printf("%s\n", ft_strrchr(envp[0], '='));
    initenvp(envp);
    return (0);
}
