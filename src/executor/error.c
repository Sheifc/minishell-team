#include "minishell.h"

int    ft_error(char *msg)
{
    if (errno)
    {
        perror("Error");
        return(errno);
    }
    else
    {
        ft_putstr_fd(msg, STDERR_FILENO);
        return(0);
    }
}
