#include "minishell.h"

char    *get_current_directory(t_shell *data)
{
    char *path;
    
    path = getcwd(NULL, 0);
    if (!path)
        ft_error(data, "Error: getcwd failed\n", 0);
    return (path);
}

void    ft_pwd(t_shell *data)
{
    char    *path;

    path = get_current_directory(data);
    printf("%s\n", path);
    free(path);
}
