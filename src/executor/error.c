#include "minishell.h"

int    ft_error(char *msg, int num)
{
    if (errno)
    {
        perror("Error");
        return(errno);
    }
    else
    {
        ft_putstr_fd(msg, STDERR_FILENO);
        return(num);
    }
}
