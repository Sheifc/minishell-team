#include "minishell.h"

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

t_cmd *create_cmd_node(void)
{
    t_cmd *node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->arg = NULL; // Inicializar como NULL
    node->fdin = -1;
    node->fdout = -1;
    node->n_args = 0; // Inicializar el número de argumentos
    node->next = NULL;
    return node;
}

int handle_redirection(t_cmd *cmd, t_token **token)
{
    if (cmd == NULL || token == NULL || *token == NULL)
        return ft_error("Invalid pointer\n", 1);
    if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
    {
        int status = ft_innout(cmd, token);
        if (status != 0)
            return status; // Indicar error
        // Saltar el siguiente token si es un argumento de la redirección
        if (*token && (*token)->type == WORD)
            *token = (*token)->next;
    }
    return 0; // Indicar éxito
}


void    add_argument(t_cmd *cmd, char *arg)
{
    char    **new_arg;
    int i;
    
    i = 0;
    new_arg = (char **)malloc(sizeof(char *) * (cmd->n_args + 2)); // +2 para el nuevo argumento y NULL al final
    if (!new_arg)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    while (i < cmd->n_args)
    {
        new_arg[i] = cmd->arg[i];
        i++;
    }
    new_arg[cmd->n_args] = ft_strdup(arg);
    new_arg[cmd->n_args + 1] = NULL;
    free(cmd->arg);
    cmd->arg = new_arg;
    cmd->n_args++;
}

int fill_cmd_args(t_cmd *cmd, t_token **token)
{
    int status = 0;
    while (*token && (*token)->type != PIPE)
    {
        if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
            status = handle_redirection(cmd, token);
        else if ((*token)->type == WORD || (*token)->type == QUOTE || (*token)->type == DQUOTE)
        {
            add_argument(cmd, (*token)->content);
            *token = (*token)->next;
        }
        else
            *token = (*token)->next; // Avanzar al siguiente token si no es un argumento o redirección
        if (status != 0)
            break; // Salir si hay un error en la redirección
    }
    return status;
}


int add_cmd_to_shell(t_cmd **cmd_list, t_token **token)
{
    t_cmd *new_cmd = create_cmd_node();
    if (!new_cmd)
        return 1; // Error al crear el nodo de comando
    int status = fill_cmd_args(new_cmd, token);
    if (status == 0)
        add_cmd_to_list(cmd_list, new_cmd);
    else
        free(new_cmd); // Liberar el nuevo comando si hubo un error
    return status;
}


void fill_struct(t_shell *data)
{
    while (data->token)
    {
        if (data->token->type != PIPE)
        {
            int status = add_cmd_to_shell(&data->cmd, &data->token);
            if (status != 0)
            {
                // Manejar el error adecuadamente, por ejemplo, limpiando estructuras
                clear_structs(&data->token, &data->cmd);
                break; // Salir si hay un error
            }
        }
        else if (data->token->type == PIPE)
        {
            data->token = data->token->next;
        }
    }
}

