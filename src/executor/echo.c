#include "minishell.h"

static void print_args(t_cmd *args, int i, int newline)
{
    while (args->arg[i])
    {
        printf("%s", args->arg[i]);
        if (args->arg[i + 1]) //comprueba si hay otro arg despues del actual y sino es asi, no imprime el espacio
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}

void	ft_echo(t_cmd *args)
{
    int i; //comando
    int j; //caracter dentro del comando
    int newline; // flag para la presencia de \n x defecto está presente, si tuviera la flag -n, el \n desaparece

    i = 1;
    j = 1;
    newline = 1;
    while (args->arg[i] && args->arg[i][0] == '-')
    {
        i++;
        while (args->arg[1][j] == 'n')
        {
            newline = 0; //eliminamos \n si hay -n
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
// echo $user imprime pgonzal en bash gestión del parser cuando trate la expansión de variables