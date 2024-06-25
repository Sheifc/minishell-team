#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    //(void)argc; 
    //(void)argv;
    (void)envp;

    t_cmd cmd = { .arg = &argv[1], .n_args = argc, .fdinf = -1, .fdoutf = -1};
    execute_builtin((&cmd));
    return 0;

    // Crear diferentes conjuntos de argumentos para probar ft_echo
    /* char *args1[] = {"echo", NULL};
    char *args2[] = {"echo", "-n", NULL};
    char *args3[] = {"echo", "hola", NULL};
    char *args4[] = {"echo", "-n", "hola", NULL};
    char *args5[] = {"echo", "hola", "-n", NULL};
	char *args6[] = {"echo", "-n", "-n", "hola", NULL};
    char *args7[] = {"echo", "-n", "-n", "-n", "hola", NULL};
    char *args8[] = {"echo", "-nn", "hola", NULL};
    char *args9[] = {"echo", "-nhola", NULL};
    char *args10[] = {"echo", "-nnnnn", "hola", NULL};
    char *args11[] = {"echo", "-nn-nnn", "hola", NULL};
    char *args12[] = {"echo", "hola", "-nnnholannnnn", NULL};

    t_cmd cmd1 = { .argv = args1, .n_args = 1, .fdinf = -1, .fdoutf = -1, .path = NULL };
	t_cmd cmd2 = { .argv = args2, .n_args = 2, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd3 = { .argv = args3, .n_args = 2, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd4 = { .argv = args4, .n_args = 3, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd5 = { .argv = args5, .n_args = 3, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd6 = { .argv = args6, .n_args = 4, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd7 = { .argv = args7, .n_args = 5, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd8 = { .argv = args8, .n_args = 3, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd9 = { .argv = args9, .n_args = 2, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd10 = { .argv = args10, .n_args = 3, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd11 = { .argv = args11, .n_args = 3, .fdinf = -1, .fdoutf = -1, .path = NULL };
    t_cmd cmd12 = { .argv = args12, .n_args = 3, .fdinf = -1, .fdoutf = -1, .path = NULL };

    // Probar ft_echo con diferentes argumentos
    ft_printf("Test 1: ");
    execute_builtin(&cmd1); // Output:\n
    ft_printf("Output:\n");

	ft_printf("Test 2: ");
    execute_builtin(&cmd2); // Output:
    ft_printf("Output:");

    ft_printf("Test 3: ");
    execute_builtin(&cmd3); // Output: hola\n
    ft_printf("Output: hola\n");

    ft_printf("Test 4: ");
    execute_builtin(&cmd4); // Output: hola
    ft_printf("Output: hola");

    ft_printf("Test 5: ");
    execute_builtin(&cmd5); // Output: hola -n\n
    ft_printf("Output: hola -n\n");

    ft_printf("Test 6: ");
    execute_builtin(&cmd6); // Output: hola
    ft_printf("Output: hola");

    ft_printf("Test 7: ");
    execute_builtin(&cmd7); // Output: hola
    ft_printf("Output: hola");

    ft_printf("Test 8: ");
    execute_builtin(&cmd8); // Output: hola
    ft_printf("Output: hola");

    ft_printf("Test 9: ");
    execute_builtin(&cmd9); // Output: -nhola\n
    ft_printf("Output: -nhola\n");

    ft_printf("Test 10: ");
    execute_builtin(&cmd10); // Output: hola
    ft_printf("Output: hola");

    ft_printf("Test 11: ");
    execute_builtin(&cmd11); // Output: -nn-nnn hola\n
    ft_printf("Output: -nn-nnn hola\n");

    ft_printf("Test 12: ");
    execute_builtin(&cmd12); // Output: hola -nnnholannnnn\n
    ft_printf("Output: hola -nnnholannnnn\n");

    return (0); */
}