# Requirements:

We are required to build a mini shell (command-line interpreter) that mimics the bash, hence the name it wouldn’t be doing all the work that bash does, but the basic functionality:

The shell will work only in interactive mode (no scripts, i.e. the executable takes no arguments)
Run simple commands with absolute, relative path (e.g. /bin/ls, ../bin/ls)
Run simple commands without a path (e.g. ls, cat, grep, etc…)
Have a working history (you can navigate through commands with up/down arrows)
Implement pipes (|)
Implement redirections (<, >, >>)
Implement the here-doc (<<)
Handle double quotes ("") and single quotes (''), which should escape special characters, beside $ for double quotes.
Handle environment variables ($ followed by a sequence of characters).
Handle signals like in bash (ctrl + C, ctrl + \, ctrl + D).
Implement the following built-ins:
— echo (option -n only)
— exit
— env (with no options or arguments)
— export (with no options)
— unset (with no options)
— cd
— pwd
And for the bonus part (optional, but i did it, because it’s cool!)
— handle && and || with the parenthesis () for priority.
— handle * wildcards for the current working directory.

# The expansion of environment variables:

I don’t know the exact way bash expands environment variables, but I came up with my own way, and it is composed of few steps illustrated with an example.

Let’s set a variable A with the value 1.
export A="1"
Let’s suppose we get the following user input:
""$A B "CD"
The first thing with do, is to replace $A with its value, so it becomes:
""1 B "CD"
Then we get rid of empty strings, so we get:
1 B "CD"
Then we split the string by spaces (depending on the quotes), so we get three strings:
1 , B, "CD"
Then we check if there is any globbing (* wildcard), if there is we replace the wildcard by the appropriate strings — the globbing algorithm wasn’t mine, I looked it up on the internet, it’s a backtracking algorithm, you can learn more about it here.
Finally, we strip out any quotes:
1 , B, CD

https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218


# Del subject:

Tu shell deberá:

• Mostrar una entrada mientras espera un comando nuevo.
• Tener un historial funcional.

• Buscar y ejecutar el ejecutable correcto (basado en la variable PATH o mediante el uso de rutas relativas o absolutas).

• Evita utilizar más de una variable global para indicar la recepción de una señal. Piensa en lo que implica: Esta aproximación evita que tu gestor de señales acceda a tus estructuras de datos principales.

• No interpretar comillas sin cerrar o caracteres especiales no especificados en el enunciado como \ (barra invertida) o ; (punto y coma).
• Gestionar que la ’ evite que el shell interprete los metacaracteres en la secuencia entrecomillada.
• Gestionar que la " evite que el shell interprete los metacaracteres en la secuencia entrecomillada exceptuando $ (signo de dólar).

## Redirecciones

• Implementar redirecciones:
◦ < debe redirigir input.
◦ > debe redirigir output.
◦ “<<” debe recibir un delimitador, después leer del input de la fuente actual hasta que una línea que contenga solo el delimitador aparezca. Sin embargo, no necesita actualizar el historial.
◦ “>>” debe redirigir el output en modo append.

## Executor

• Implementar pipes (carácter |). El output de cada comando en la pipeline se
conecta a través de un pipe al input del siguiente comando.
• Gestionar las variables de entorno ($ seguidos de caracteres) que deberán ex- pandirse a sus valores.
• Gestionar $?, que deberá expandirse al estado de salida del comando más reciente ejecutado en la pipeline.

## Señales

• Gestionar ctrl-C ctrl-D ctrl-\, que deberán funcionar como en bash.
• Cuando sea interactivo:
◦ ctrl-C imprime una nueva entrada en una línea nueva. ◦ ctrl-D termina el shell.
◦ ctrl-\ no hace nada.

## Deberá implementar los built-ins:
◦ echo con la opción -n.
◦ cd solo con una ruta relativa o absoluta. 
◦ pwd sin opciones.
◦ export sin opciones.
◦ unset sin opciones.
◦ env sin opciones o argumentos. 
◦ exit sin opciones.
