Makefile: env.c exit.c export.c unset.c \
				executor.c path.c

#include "minishell.h"

// main para ls
/* int	main(int argc, char **argv, char **envp)
{
	(void)argc; 
	(void)argv;
	(void)envp;

	char **mock_args = malloc(sizeof(char*) * 10);
	if (mock_args == NULL)
	{
		perror("malloc");
		return (1);
	}
	mock_args[0] = "ls";
	mock_args[1] = "-l";
	mock_args[2] = NULL;
	// Inicializar el comando mock para ls
	t_cmd mock_ls = {
		.path = "/bin/ls",
		.argv = mock_args,
		.argc = 2,
		.fdinf = -1,
		.fdoutf = -1
	};
	t_shell mock = {
		.cmd = &mock_ls,
		.env = NULL,
		.command = NULL,
		.fd = {-1, -1}
	};
	// Añadir el comando mock a la lista de comandos en mock
    t_list *new_node = ft_lstnew((void *)&mock_ls);
    if (!new_node)
    {
        perror("ft_lstnew");
        free(mock_args);
        return (1);
    }
    mock.command = new_node;
	//execute(mock.command, &mock);

    // Liberar memoria asignada
    free(mock_args);
    ft_lstclear(&(mock.command), free);
	return (0);
} */
// para parseo:
	// char *line = readline("minishell$ ");
	// while (line)
	// {
	// 	add_history(line);
	// 	free(line);
	// 	line = readline("minishell$ ");
	// }

// main para echo:

int main(int argc, char **argv, char **envp)
{
    (void)argc; 
    (void)argv;

    // Simular variables de entorno y path
    char *path[] = {"/bin", "/usr/bin", NULL};
    t_env env = {
        .env = envp,
        .path = path,
        .export = NULL
    };

    // Crear argumentos mock para el comando "echo"
    char **echo_args = malloc(sizeof(char*) * 4);
    if (echo_args == NULL)
    {
        perror("malloc");
        return (1);
    }
    echo_args[0] = "echo";
    echo_args[1] = "-n";
    echo_args[2] = "Hello, world!";
    echo_args[3] = NULL; // Terminar el array con NULL

    // Inicializar el comando mock para echo
    t_cmd echo = {
        .argv = echo_args,
        .argc = 3,
        .fdinf = -1,  // Inicializa con valores por defecto
        .fdoutf = -1, // Inicializa con valores por defecto
        .path = "/bin/echo" // Ruta completa del ejecutable, aunque no se usa en este caso
    };

    // Inicializar la estructura de shell mock
    t_shell data = {
        .cmd = &echo,
        .env = &env,
        .command = NULL,  // Inicializar la lista de comandos
        .fd = {-1, -1}    // Inicializar los descriptores de archivo con valores por defecto
    };

    // Añadir el comando mock a la lista de comandos en mock
    t_list *new_node = ft_lstnew((void *)&echo);
    if (!new_node)
    {
        perror("ft_lstnew");
        free(echo_args);
        return (1);
    }
    data.command = new_node;

    // Aquí puedes llamar a tu función de ejecución usando el mock
    //execute(mock.command, &mock);
	ft_echo(&data);

    // Liberar memoria asignada
    free(echo_args);
    ft_lstclear(&(data.command), free);

    return (0);
}