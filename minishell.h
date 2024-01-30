#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_lex {
    char            *great;
    char            *less;
    char            *great2;
    char            *less2;
    struct s_lex    *next;
} t_lex;

#endif