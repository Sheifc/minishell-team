#include "minishell.h"

void clear_structs(t_token **token, t_cmd **cmd)
{
    t_token *current_token = *token;
    t_cmd *current_cmd = *cmd;
    t_cmd *next_cmd;
    t_token *next_token;

    while (current_token != NULL)
    {
        next_token = current_token->next;
        printf("Freeing token: %p\n", current_token);
        free(current_token);
        current_token = next_token;
    }
    while (current_cmd != NULL)
    {
       if(current_cmd->fdin != -1)
        {
            printf("Closing fdin: %d\n", current_cmd->fdin);
            close(current_cmd->fdin);
        }
        if(current_cmd->fdout != -1)
        {
            printf("Closing fdout: %d\n", current_cmd->fdout);
            close(current_cmd->fdout);
        }
        next_cmd = current_cmd->next;
        printf("Freeing cmd: %p\n", current_cmd);
        free(current_cmd);
        current_cmd = next_cmd;
    }
    *cmd = NULL;
    *token = NULL;
}
