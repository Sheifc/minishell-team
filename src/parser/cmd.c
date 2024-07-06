#include "minishell.h"

int count_commands(t_token *token)
{
    int count = 0;
    while (token)
    {
        if (token->type == PIPE)
            count++;
        token = token->next;
    }
    return (count + 1);
}

void token_to_cmd(t_token *token_list, t_cmd **cmd_list)
{
    t_cmd   *new_cmd;
    t_cmd   *current_cmd;
    t_token *current_token;
    int     i;
    int     cmd_count;

    if (!token_list)
        return;
    *cmd_list = NULL;
    current_cmd = NULL;
    current_token = token_list;
    cmd_count = count_commands(current_token);
    while (cmd_count > 0 && current_token)
    {
        new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
        if (!new_cmd)
        {
            free_cmd_list(cmd_list);
            return;
        }
        new_cmd->n_args = count_args(current_token);
        new_cmd->arg = (char **)malloc(sizeof(char *) * (new_cmd->n_args + 1));
        if (!new_cmd->arg)
        {
            free(new_cmd);
            free_cmd_list(cmd_list);
            return;
        }
        i = 0;
        while (current_token && current_token->type != PIPE)
        {
            if (current_token->type == WORD)
            {
                new_cmd->arg[i] = strdup(current_token->content);
                if (!new_cmd->arg[i])
                {
                    free_cmd(new_cmd);
                    free_cmd_list(cmd_list);
                    return;
                }
                i++;
            }
            current_token = current_token->next;
        }
        new_cmd->arg[i] = NULL;
        new_cmd->fdin = -1;
        new_cmd->fdout = -1;
        new_cmd->next = NULL;
        if (*cmd_list == NULL)
            *cmd_list = new_cmd;
        else
            current_cmd->next = new_cmd;
        current_cmd = new_cmd;
        if (current_token && current_token->type == PIPE)
            current_token = current_token->next;
        cmd_count--;
    }
}
