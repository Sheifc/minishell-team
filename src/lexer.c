# include "../includes/minishell.h"
# include "../includes/structures.h"

void odd_even_marks(int marks)
{
    if(marks % 2 == 0)
        ft_printf("ejecuta\n");
    else if(marks % 2 != 0)
        ft_printf("\0");
}

void lexer(char *str_cmd)
{
    int i;
    int marks;

    i = 0;
    while(str_cmd[i])
    {
        marks = quo_marks(str_cmd[i], str_cmd);
        i++;
    }
    odd_even_marks(marks);
}
