#include "minishell.h"

void    ft_error(char *msg)
{
    ft_putstr_fd(msg, STDERR_FILENO);
    exit(EXIT_FAILURE);
}

void    print_error(char *msg)
{
    ft_putstr_fd(msg, STDERR_FILENO);
}

/* int	print_error_cd(char *dir)
{
	return (print_error("cd", dir, strerror(errno), 1));
} */
