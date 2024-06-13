# include "minishell.h"

/* void quotes(char *str_cmd, int *i, t_token *tok)
{
    int j;
    int flagsq;
    int flagdq;

    flagsq = 1;
    flagdq = 1;
    j = &i;
    while(str_cmd[j])
    {
        if(str_cmd[j] == '\'')
            flagsq++;
        else if(str_cmd[j] == '"')
            flagdq++;
    }
} */

void lexer(char *str_cmd)
{
    int i;
    t_token *tok;

    tok = NULL;
    i = 0;
    while(str_cmd[i])
    {
        if(str_cmd[i] == '|')
            set_token(PIPE, str_cmd, &tok, &i);
        /* else if(str_cmd[i] == '<')
            set_token(IN, str_cmd, &tok, &i);
        else if(str_cmd[i] == '>')
            set_token(OUT, str_cmd, &tok, &i);
        else if(str_cmd[i] == '\'' || str_cmd[i] == '"')
            printf("comillas");
        else if(str_cmd[i] != '|' && str_cmd[i] != '<' && str_cmd[i] != '>' && str_cmd[i] != '\'' && str_cmd[i] != '"' && str_cmd[i] != ' ')
            set_token(WORD, str_cmd, &tok, &i); */
        else
            i++;
    }
    //print_lists(tok);
}
