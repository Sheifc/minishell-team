#include "minishell.h"

void add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
    t_cmd *temp;
    printf("llega a add_cmd_to_list\n");
    if (!new_cmd){
        printf("new_cmd es NULL, retornando\n");
        return ;}
    if (*head == NULL){
        printf("*head es NULL, asignando new_cmd a *head\n");
        *head = new_cmd;}
    else
    {
        temp = *head;
        printf("*head no es NULL, recorriendo la lista\n");
        while (temp->next != NULL){
            printf("Nodo actual: %p, siguiente nodo: %p\n", (void*)temp, (void*)temp->next);
            temp = temp->next;}
        printf("Último nodo encontrado: %p, asignando new_cmd: %p a temp->next\n", (void*)temp, (void*)new_cmd);
        temp->next = new_cmd;
    }
    printf("add_cmd_to_list terminado\n");
}

t_cmd   *create_cmd_node(void)
{
    t_cmd *node = (t_cmd *)malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->arg = NULL;
    node->fdin = -1;
    node->fdout = -1;
    node->n_args = 0;
    node->next = NULL;
    return (node);
}

void    add_argument(t_shell *data, t_cmd *cmd, char *token_content)
{
    char **new_arg;
    int i;

    i = 0;
    new_arg = (char **)malloc(sizeof(char *) * (cmd->n_args + 2));
    if (!new_arg)
        ft_error(data, "Error allocating memory", 1);
    while (i < cmd->n_args)
    {
        new_arg[i] = cmd->arg[i];
        i++;
    }
    printf("cmd->n_args: %d\n", cmd->n_args);
    printf("new_arg: %p\n", (void*)new_arg);
    new_arg[cmd->n_args] = ft_strdup(token_content);
    printf("new_arg[cmd->n_args]: %s\n", new_arg[cmd->n_args]);
    new_arg[cmd->n_args + 1] = NULL;
    cmd->arg = new_arg;
    printf("cmd->arg: %p\n", (void*)cmd->arg);
    cmd->n_args++;
    printf("Added argument: %s\n", token_content);
    print_argu(cmd->arg);
}

int handle_redirection(t_shell *data, t_cmd *cmd, t_token **token)
{
    int status;

    status = 0;
    if (cmd == NULL || token == NULL || *token == NULL)
    {
        ft_error(data, "Invalid pointer\n", 1);
        return (1);
    }
    printf("Handling redirection: %s %u\n", (*token)->content, (*token)->type);
    if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
    {
        printf("entra: %s %u\n", (*token)->content, (*token)->type);
        status = ft_innout(data, cmd, token);
        printf("despues function save file token->content: %s\n", (*token)->content);
        if (status != 0)
            return (status);
    }
    return (0);
}

int fill_cmd_args(t_shell *data, t_cmd *cmd, t_token **token)
{
    int status;
    
    status = 0;
    while (*token && (*token)->type != PIPE)
    {
        if ((*token)->type == IN || (*token)->type == OUT || (*token)->type == APPEND || (*token)->type == HEREDOC)
        {
            status = handle_redirection(data, cmd, token);
            if (status != 0)
                break ;
        }
        else if ((*token)->type == WORD || (*token)->type == QUOTE || (*token)->type == DQUOTE)
        {
            printf("Token content before adding argument: %s\n", (*token)->content);
            add_argument(data, cmd, (*token)->content);
            printf("sale de add argument: %s\n", (*token)->content);
            *token = (*token)->next;
        }
        else
            *token = (*token)->next;
    }
    printf("acaba fill_cmd_args\n  ");
    return (status);
}

int add_cmd_to_shell(t_shell *data, t_cmd **cmd_list, t_token **token)
{
    t_cmd *new_cmd;
    int status;
    
    new_cmd = create_cmd_node();
    status = 0;
    if (!new_cmd)
        return (1);
    printf("Current token en add_cmd_to_shell: %s (type: %d)\n", data->token->content, data->token->type);
    status = fill_cmd_args(data, new_cmd, token);
    printf("Status en cmd_to_shell: %d\n", status);
    if (status == 0)
        add_cmd_to_list(cmd_list, new_cmd);
    else
        free_cmd(&new_cmd);
    printf("Lista de comandos: final add_cmd_to_shell \n");
    print_cmd_list(*cmd_list);
    return (status);
}

void token_to_cmd(t_shell *data)
{
    int status; 

    status = 0;
    while (data->token)
    {
        printf("Current token: %s (type: %d)\n", data->token->content, data->token->type);
        if (data->token->type != PIPE)
        {
            status = add_cmd_to_shell(data, &data->cmd, &data->token);
            printf("Status: %d\n", status);
            if (status != 0)
            {
                clear_structs(&data->token, &data->cmd);
                break ;
            }
        }
        else if (data->token->type == PIPE)
            data->token = data->token->next;
    }
    printf("Token to cmd finished\n");
}
