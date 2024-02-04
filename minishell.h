#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"

typedef struct s_lex {
    char            *type;
    char            *str;
} t_lex;

typedef struct s_table {
    char    *infile;
    char    *outfile;
    int     append;
    t_list  *cmd_lst;
}   t_table;

#endif