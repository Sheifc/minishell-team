#include "minishell.h"

int only_spaces(char *str_cmd)
{
    int i;

    i = 0;
    while(str_cmd[i])
    {
        if(str_cmd[i] != ' ')
            return(0);
        i++;
    }
    return(1);
}
