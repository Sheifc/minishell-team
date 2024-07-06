# include "minishell.h"

void    print_lists(t_token *tok)
{
    t_token *aux;
    int i;

    i = 1;
    aux = tok;
    printf("%sLIST%s\n", C, RST);
    while (aux)
    {
        printf("%sNode: %d%s\n", RED, i++, RST);
        printf("%sContent: %s%s%s\n", W, Y, aux->content, RST);
        if(aux->type == PIPE)
            printf("%sType: %sPIPE%s\n", G, Y, RST);
        else if(aux->type == IN)
            printf("%sType: %sIN%s\n", G, Y, RST);
        else if(aux->type == OUT)
            printf("%sType: %sOUT%s\n", G, Y, RST);
        else if(aux->type == APPEND)
            printf("%sType: %sAPPEND%s\n", G, Y, RST);
        else if(aux->type == QUOTE)
            printf("%sType: %sQUOTE%s\n", G, Y, RST);
        else if(aux->type == DQUOTE)
            printf("%sType: %sDQUOTE%s\n", G, Y, RST);
        else if(aux->type == HEREDOC)
            printf("%sType: %sHEREDOC%s\n", G, Y, RST);
        else if(aux->type == WORD)
            printf("%sType: %sWORD%s\n", G, Y, RST);
        aux = aux->next;
    }
}

void    print_cmd_list(t_cmd *cmd)
{
    int count;

    if (cmd == NULL){
        printf("Command list is empty.\n");
        return;}
    while (cmd)
    {
        count = 0;
        while (cmd->arg[count])
        {
            printf("Arg[%d]: %s\n", count, cmd->arg[count]);
            count++;
        }
        printf("N_args: %d\n", cmd->n_args);
        printf("FD_IN: %d\n", cmd->fdin);
        printf("FD_OUT: %d\n", cmd->fdout);
        cmd = cmd->next;
    }
}
