#include "minishell.h"

void free_token(t_token **token)
{
	printf("token: %p\n", token);
    if (!token || !*token)
        return;
    free((*token)->content);
	dprintf(2, "freeing token: %p\n", *token);
    free(*token);
    *token = NULL;
}

void free_token_list(t_token **token_list)
{
    t_token *current;
    t_token *next;

	printf("token_list: %p\n", token_list);
    if (!token_list || !*token_list)
        return;
    current = *token_list;
    while (current)
    {
        next = current->next;
        free_token(&current);
        current = next;
    }
    *token_list = NULL;
}
