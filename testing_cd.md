Testing: 

1. Cambio al directorio HOME:

Ejecuta cd sin argumentos.
Verifica que cambia al directorio HOME correctamente.

2. Cambio a un directorio relativo:

Cambia a un subdirectorio, por ejemplo, cd subdirectory.

3. Cambio a un directorio absoluto:

Cambia a un directorio absoluto, por ejemplo, cd /usr/local.

4. Cambio al directorio anterior (OLDPWD):

Ejecuta cd - para verificar que cambia al directorio anterior.

5. Manejo de directorios inexistentes:

Intenta cambiar a un directorio inexistente para verificar el manejo de errores, por ejemplo, cd nonexistent_directory.

6. Manejo de permisos:

Intenta cambiar a un directorio sin permisos de lectura o escritura para verificar el manejo de errores de permisos.

# Ejemplos de pruebas: 

./minishell cd
Directorio actual: /Users/sheila/Desktop/minishell
Nuevo directorio actual: /Users/sheila

./minishell cd subdirectory
Directorio actual: /Users/sheila
Nuevo directorio actual: /Users/sheila/subdirectory

./minishell cd /usr/local
Directorio actual: /Users/sheila/subdirectory
Nuevo directorio actual: /usr/local

./minishell cd -
Directorio actual: /usr/local
/Users/sheila/subdirectory
Nuevo directorio actual: /Users/sheila/subdirectory

./minishell cd nonexistent_directory
Directorio actual: /Users/sheila/subdirectory
Error: path not found

./minishell cd /root
Directorio actual: /Users/sheila/subdirectory
Error: Permission denied
