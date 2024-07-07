#include "minishell.h"

char    *get_current_directory(void)
{
    char *path;
    
    path = getcwd(NULL, 0);
    if (!path)
        perror("Error: getcwd failed");
    return (path);
}

void    ft_pwd(void)
{
    char    *path;

    path = get_current_directory();
    printf("%s\n", path);
    free(path);
}
