#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"

typedef struct s_lex {
    char            *great;
    char            *less;
    char            *great2;
    char            *less2;
    struct s_lex    *next;
} t_lex;

#endif