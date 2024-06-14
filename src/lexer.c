# include "minishell.h"

void init_struct(t_token **tok)
{
    *tok = (t_token *)malloc(sizeof(t_token));
    (*tok)->content = NULL;
    (*tok)->type = 0;
    (*tok)->next = NULL;
}

void lexer(char *str_cmd)
{
    int i;
    t_token *tok;

    init_struct(&tok);
    i = 0;
    while(str_cmd[i])
    {
        if(str_cmd[i] == '|')
            set_token(PIPE, str_cmd, &tok, &i);
        else if(str_cmd[i] == '<')
            set_token(IN, str_cmd, &tok, &i);
        else if(str_cmd[i] == '>')
            set_token(OUT, str_cmd, &tok, &i);
        else if(str_cmd[i] == '\'' || str_cmd[i] == '"')
        {
            printf("comillas");
            i++;
        }
        else if(str_cmd[i] != '|' && str_cmd[i] != '<' && str_cmd[i] != '>' && str_cmd[i] != '\'' && str_cmd[i] != '"' && str_cmd[i] != ' ')
            set_token(WORD, str_cmd, &tok, &i);
        else
            i++;
    }
    print_lists(tok);
}
