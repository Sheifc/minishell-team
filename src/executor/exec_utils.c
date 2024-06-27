#include "minishell.h"

void ft_swap(char **a, char **b)
{
    char *aux;
    aux = *a;
    *a = *b;
    *b = aux;
}
