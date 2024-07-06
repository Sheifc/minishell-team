#include "minishell.h"

void    ft_error(t_shell *data, char *msg, int num)
{
    if (errno)
    {
        perror("Error");
        data->error_code = errno;
    }
    else
    {
        ft_putstr_fd(msg, STDERR_FILENO);
        data->error_code = num;
        return ;
    }
}
