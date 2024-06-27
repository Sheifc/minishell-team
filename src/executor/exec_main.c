#include "minishell.h"

/* int main(int argc, char **argv, char **envp)
{
    t_shell data;
    t_cmd *cmd = malloc(sizeof(t_cmd) * argc - 1);
    int i = 0;
    while (++i < argc)
    {
        char **args = malloc(sizeof(char *) * 2);
        args[0] = argv[i];
        args[1] = NULL;
        cmd[i-1].arg = args;
        cmd[i-1].n_args = 1;
        cmd[i-1].fdin = -1;
        cmd[i-1].fdout = -1;
        cmd[i-1].next = ((i < argc - 1) ? &cmd[i+1] : NULL);
    }
    data.cmd = cmd;
    data.cmd->n_args = argc;
    data.envp = envp;
    data.env = NULL;
    data.export = NULL;
    data.path = NULL;
    data.status = 0;
    data.line = NULL;

    //init_stack(&data, argc - 1, &argv[1], envp);
    init_env(&data, envp);
    executor(&data);
    // Liberar la memoria asignada
    for (int j = 0; j < argc - 1; j++) {
        free(cmd[j].arg);
    }
    free(cmd);  // Liberar la lista de argumentos tras el parseo
    free_env_list(data.env);  // Liberar la lista de entorno
    free_env_list(data.export);
    return (0);
} */

