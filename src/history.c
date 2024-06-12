# include "../includes/minishell.h"
# include "../includes/structures.h"

void history(char *str_cmd)
{
    if(str_cmd && *str_cmd)
        add_history(str_cmd);
}