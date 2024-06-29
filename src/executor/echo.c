#include "minishell.h"

static void print_args(t_cmd *args, int i, int newline)
{
    while (args->arg[i])
    {
        printf("%s", args->arg[i]);
        if (args->arg[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}

void	ft_echo(t_cmd *args)
{
    int i;
    int j;
    int newline;

    i = 1;
    j = 1;
    newline = 1;
    while (args->arg[i] && args->arg[i][0] == '-')
    {
        i++;
        while (args->arg[1][j] == 'n')
        {
            newline = 0;
            j++;
        }
        if (args->arg[1][j] != '\0')
        {
            newline = 1;
            i--;
            break;
        }
    }
    print_args(args, i, newline);
}
