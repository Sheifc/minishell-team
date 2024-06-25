# echo

bash-3.2$ echo -n -n "hola"
holabash-3.2$ echo "hola"
hola
bash-3.2$ echo "hola" -n 
hola -n
bash-3.2$ echo -n "hola"
holabash-3.2$ echo -n -n -n "hola"
holabash-3.2$ echo -nn "hola"
hola

bash-3.2$ echo -nhola
-nhola
bash-3.2$ echo -nnnnn hola
holabash-3.2$ echo -nn-nnn hola
-nn-nnn hola
echo -nn hola

# pwd

La función getcwd en C es responsable de obtener el directorio de trabajo actual y almacenarlo en un buffer proporcionado por el usuario. El buffer no toma la ruta por sí solo; en cambio, getcwd escribe la ruta en el buffer que tú proporcionas.

char *getcwd(char *buf, size_t size);

buf: un puntero a un buffer donde se almacenará la ruta.
size: el tamaño del buffer.

Cómo getcwd escribe en el buffer:
getcwd accede al sistema de archivos del sistema operativo y obtiene la ruta del directorio de trabajo actual.
Escribe esta ruta en el buffer proporcionado (buffer en este caso).
Devuelve el puntero al buffer, lo que permite que otras partes del programa accedan a la ruta almacenada en buffer.

Sí, la función getcwd puede reservar dinámicamente memoria si se le pasa NULL como primer argumento y 0 como segundo argumento. Aquí está cómo funciona:

Uso de getcwd con Reserva Dinámica

char *getcwd(char *buf, size_t size);

buf = NULL y size = 0: Si buf es NULL y size es 0, getcwd asignará dinámicamente un buffer suficientemente grande para contener el path actual, utilizando malloc. En este caso, getcwd devuelve un puntero a este buffer.

```c
// Mi primera implementación: 
void	ft_pwd(void)
{
	char buffer[PATH_MAX];

	if (!getcwd(buffer, sizeof(buffer)))
        ft_error("Error: getcwd failed\n");
    ft_printf("%s\n", buffer);
}
```

# chdir

El comando chdir en bash es una llamada al sistema que cambia el directorio de trabajo actual del proceso que lo invoca. En el contexto de una shell como bash, esto significa que cambia el directorio en el que la shell está operando, afectando todos los comandos ejecutados después de este cambio.

int chdir(const char *path);

path: El nuevo directorio de trabajo.
Retorno: Devuelve 0 en caso de éxito y -1 en caso de error.

¿Qué hace chdir en bash?
Cambia el directorio de trabajo actual: La llamada al sistema chdir cambia el directorio de trabajo del proceso. En bash, esto significa que la shell cambia el directorio en el que se está trabajando, lo cual afecta todos los comandos subsiguientes.
Actualiza las variables de entorno PWD y OLDPWD: Bash mantiene y actualiza las variables de entorno PWD (current directory) y OLDPWD (previous directory) para reflejar el cambio de directorio.

# getenv

char *getenv(const char *name);

# exit

bash: 

➜  minishell git:(main) ✗ bash
bash-3.2$ exit 0
exit

bash-3.2$ exit 1
exit

bash-3.2$ exit 127
exit

bash-3.2$ exit hola
exit
bash: exit: hola: numeric argument required

bash-3.2$ exit 0 1
exit
bash: exit: too many arguments

bash-3.2$ exit -1
exit

➜  minishell git:(main) ✗ ./minishell         
➜  minishell git:(main) ✗ ./minishell exit
exit
➜  minishell git:(main) ✗ ./minishell exit 1
exit
➜  minishell git:(main) ✗ ./minishell exit a
exit: a numeric argument required
➜  minishell git:(main) ✗ ./minishell exit -
exit
➜  minishell git:(main) ✗ ./minishell exit -1 
exit
➜  minishell git:(main) ✗ ./minishell exit 1 2
exit: too many arguments

# unset

Una función de buscar la variable (key)
Otra función que libere el nodo cuando la encuentre y apuntar el nodo temporal al siguiente.