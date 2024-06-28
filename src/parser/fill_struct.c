#include "minishell.h"

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
t_cmd *create_cmd_node(void)
{
    t_cmd *node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!node)
        return NULL;
    node->arg = NULL; // Inicializar como NULL
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

void add_argument(t_cmd *cmd, char *arg)
{
    char **new_arg;
    
    new_arg = (char **)malloc(sizeof(char *) * (cmd->n_args + 2)); // +2 para el nuevo argumento y NULL al final
    if (!new_arg)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < cmd->n_args; i++)
        new_arg[i] = cmd->arg[i];
    new_arg[cmd->n_args] = ft_strdup(arg); // Usar strdup en lugar de ft_strdup
    new_arg[cmd->n_args + 1] = NULL;
    free(cmd->arg); // Liberar la memoria anterior
    cmd->arg = new_arg;
    cmd->n_args++;
}

void fill_cmd_args(t_cmd *cmd, t_token **token)
{
    while (*token && (*token)->type != PIPE)
    {
        if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
            handle_redirection(cmd, token);
        else if ((*token)->type == WORD || (*token)->type == QUOTE || (*token)->type == DQUOTE)
        {
            add_argument(cmd, (*token)->content);
            *token = (*token)->next;
        }
        else
            *token = (*token)->next; // Avanzar al siguiente token si no es un argumento o redirección
    }
}

void add_cmd_to_shell(t_cmd **cmd_list, t_token **token)
{
    t_cmd   *new_cmd;

    new_cmd = create_cmd_node();
    if (new_cmd)
    {
        fill_cmd_args(new_cmd, token);
        add_cmd_to_list(cmd_list, new_cmd);
    }
}

// Imprimir lista de comandos
void print_cmd_list(t_cmd *cmd)
{
    int count;
    if (cmd == NULL)
        return;
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

// Llenar estructura t_shell
void fill_struct(t_shell *data)
{
    printf("Filling shell commands...\n");
    while (data->token)
    {
        if (data->token->type != PIPE){
            printf("Adding command to shell...\n");
            add_cmd_to_shell(&data->cmd, &data->token);}
        else if (data->token->type == PIPE){
            printf("Found PIPE, moving to next token...\n");
            data->token = data->token->next;}
    }
}
