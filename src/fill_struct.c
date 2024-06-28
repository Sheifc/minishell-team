# include "minishell.h"

void	create_fill_list(t_cmd **cmd, t_token **token, int argcs)
{
    t_cmd	*aux;
    
    if (!*cmd)
        *cmd = list_empty_fill(token, argcs);
    else
    {
        aux = list_empty_fill(token, argcs);
        add_back_fill(cmd, aux);
    }
}

int count_args(t_token *token)
{
    int argc;
    int red;

    red = 0;
    argc = 0;
    while(token)
    {
        if(token->type == WORD)
            argc++;
        if(token->type == IN || token->type == OUT || token->type == APPEND || token->type == HEREDOC)
            red++;
        token = token->next;
    }
    return (argc - red);
}

void print_cmd_list(t_cmd *cmd)
{
    t_cmd *aux;
    int i;

    aux = cmd;
    while(aux)
    {
        i = 0;
        while(aux->arg[i])
        {
            printf("arg[%d]: %s\n", i, aux->arg[i]);
            i++;
        }
        printf("n_args: %d\n", aux->n_args);
        aux = aux->next;
    }
}

void fill_struct(t_shell *data)
{
    int argcs;

    argcs = count_args(data->token);
    while(data->token)
    {
        if(data->token->type != PIPE)
            create_fill_list(&data->cmd, &data->token, argcs);
        else if(data->token->type == PIPE)
            data->token = data->token->next;
    }
    print_cmd_list(data->cmd);
}
