#include "minishell.h"

static int  isnum(char *str)
{
    if (!str || str == (void *)0)
        return (-1);
    if (*str == '-' || *str == '+')
        str++;
    while(*str)
    {
        if(!ft_isdigit((unsigned char)*str))
            return (0);
        str++;
    }
    return (1);
}

/* static int exit_atoi(char *str)
{
    int     sign;
    long    num;
    int     i;

    i = 0;
    num = 0;
    sign = 1;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if ((str[i] == '+') || (str[i] == '-'))
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while ((str[i] >= '0') && (str[i] <= '9'))
    {
        num = (num * 10) + (str[i] - '0');
        ++i;
    }
    if (!num || num < INT_MIN || num > INT_MAX)
        return (255);
    return ((int)num * sign);
} */

void	ft_exit(t_shell *data, t_cmd *cmd)
{
    int exit_code;

    exit_code = 1;
    if (cmd->n_args > 2)
        ft_error(data, "exit: too many arguments\n", 1);
    else if (cmd->n_args == 2)
    {
        if (isnum(cmd->arg[1]) == 0)
        {
            printf("%s%s%s", "exit: ", cmd->arg[1], " numeric argument required\n");
            exit(255);
        }
        exit_code = ft_atoi(cmd->arg[1]);
    }
    printf("exit\n");
    exit(exit_code);
}
