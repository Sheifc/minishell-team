# include "../includes/minishell.h"
# include "../includes/structures.h"

int is_there_smarks(char c, char *str_cmd)
{
    int i;
    int count;

    count = 0;
    i = 0;
    while(str_cmd[i])
    {
        if(str_cmd[i] == c)
            count++;
        i++;
    }
    return (count);
}

int quo_marks(char c, char *str_cmd)
{
    int smarks;

    if(c == '\'')
        smarks = is_there_smarks(c, str_cmd);
    if(c == '"')
        smarks = is_there_smarks(c, str_cmd);
    return(smarks);
}