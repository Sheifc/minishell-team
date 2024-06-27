# include "minishell.h"

// Funciones auxiliares
t_cmd *get_last_cmd(t_cmd *lst)
{
    if (!lst)
        return NULL;
    while (lst->next)
        lst = lst->next;
    return lst;
}

void add_cmd_to_list(t_cmd **lst, t_cmd *new)
{
    t_cmd *last = get_last_cmd(*lst);
    if (!last)
        *lst = new;
    else
        last->next = new;
}

// Crear y llenar nodo de comando
t_cmd *create_cmd_node(int argcs)
{
    t_cmd *node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!node)
        return NULL;
    node->arg = (char **)malloc(sizeof(char *) * (argcs + 1)); // +1 para NULL al final
    if (!node->arg)
    {
        free(node);
        return NULL;
    }
    node->fdin = -1;
    node->fdout = -1;
    node->n_args = 0; // Inicializar el número de argumentos
    node->next = NULL;
    return node;
}

void handle_redirection(t_cmd *cmd, t_token **token)
{
    ft_innout(cmd, token);
    // Saltar el siguiente token si es un argumento de la redirección
    if (*token && (*token)->type == WORD)
        *token = (*token)->next;
}

void handle_word(t_cmd *cmd, t_token **token, int *arg_index)
{
    cmd->arg[*arg_index] = ft_strdup((*token)->content);
    *token = (*token)->next;
    (*arg_index)++;
    cmd->n_args = *arg_index; // Actualizar el número de argumentos en la estructura
}

void fill_cmd_args(t_cmd *cmd, t_token **token, int argcs)
{
    int i = 0;

    while (*token && (*token)->type != PIPE)
    {
        if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
            handle_redirection(cmd, token);
        else if ((*token)->type == WORD || (*token)->type == QUOTE || (*token)->type == DQUOTE)
        {
            if (i >= argcs) // Asegurarse de no escribir fuera de los límites
            {
                fprintf(stderr, "Error: too many arguments\n");
                break;
            }
            handle_word(cmd, token, &i);
        }
        else
        {
            *token = (*token)->next; // Avanzar al siguiente token si no es un argumento o redirección
        }
    }
    cmd->arg[i] = NULL;
}

void add_cmd_to_shell(t_cmd **cmd_list, t_token **token, int argcs)
{
    t_cmd *new_cmd = create_cmd_node(argcs);
    if (new_cmd)
    {
        fill_cmd_args(new_cmd, token, argcs);
        add_cmd_to_list(cmd_list, new_cmd);
    }
}

// Contar argumentos
int count_args(t_token *token)
{
    int argc = 0;
    while (token)
    {
        if (token->type == WORD)
            argc++;
        else if (token->type == IN || token->type == OUT || token->type == APPEND || token->type == HEREDOC)
        {
            // saltar el argumento siguiente que corresponde a la redirección
            if (token->next)
                token = token->next;
        }
        token = token->next;
    }
    return argc;
}

// Imprimir lista de comandos
void print_cmd_list(t_cmd *cmd)
{
    int count;
    if (cmd == NULL)
        return;
    while(cmd)
    {
        count = 0;
        while(cmd->arg[count])
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

// Llenar estructura t_shell
void fill_struct(t_shell *data)
{
    int argcs = count_args(data->token);
    while (data->token)
    {
        if (data->token->type != PIPE)
            add_cmd_to_shell(&data->cmd, &data->token, argcs);
        else if (data->token->type == PIPE)
            data->token = data->token->next;
    }
}
