# Resultados de shell

< test.txt ls -l | wc -l > outtest.txt

      14

ls -l

total 152
-rw-r--r--   1 sheferna  2023_malaga   1060 Mar 27 10:28 LICENSE
-rw-r--r--   1 sheferna  2023_malaga   2078 Apr  1 13:04 Makefile
-rw-r--r--   1 sheferna  2023_malaga      7 Mar 27 10:28 README.md
drwxr-xr-x  26 sheferna  2023_malaga    884 Apr  2 10:08 docu
drwxr-xr-x   4 sheferna  2023_malaga    136 Apr  1 13:04 includes
drwxr-xr-x  14 sheferna  2023_malaga    476 Apr  2 10:06 libft
drwxr-xr-x   3 sheferna  2023_malaga    102 Apr  2 10:06 obj
-rwx------   1 sheferna  2023_malaga     37 Apr  2 10:06 outfile.txt
-rw-r--r--   1 sheferna  2023_malaga      9 Apr  2 10:10 outtest.txt
-rwxr-xr-x   1 sheferna  2023_malaga  51136 Apr  2 10:06 pipex
drwxr-xr-x   4 sheferna  2023_malaga    136 Apr  1 17:04 src
drwxr-xr-x   3 sheferna  2023_malaga    102 Apr  1 13:04 src_bonus
-rw-r--r--   1 sheferna  2023_malaga     14 Apr  1 16:58 test.txt

wc -l

       0

ls

LICENSE		docu		obj		pipex		test.txt
Makefile	includes	outfile.txt	src
README.md	libft		outtest.txt	src_bonus

wc

       0       0       0

< test.txt ls -l | awk '{count++} END {printf count}' > outtest.txt
16

< test.txt "ls -l" | "awk '{count++} END {printf count}'"
outtest.txt
16

# Resultados de pipex

./pipex infile.txt "ls -l" "wc -l" outfile.txt

      14


# Bonus

./pipex test.txt "ls -l" "awk '{count++} END {printf count}'" outfile.txt
/bin/ls
/usr/bin/awk
awk: syntax error at source line 1
 context is
         >>> ' <<<
awk: bailing out at source line 1
➜  Pipex git:(master) ✗ ls << limit | cat >> outfile
pipe heredoc> hola
pipe heredoc> sfawf
pipe heredoc> waegwarerg
pipe heredoc> limit
➜  Pipex git:(master) ✗ ./pipex here_doc limit ls cat outfil
No correct arguments: Undefined error: 0
➜  Pipex git:(master) ✗ ls << limit | cat >> outfie
hola
sfawf
waegwarerg
limit
➜  Pipex git:(master) ✗ ls << limit | cat >> outfie
pipe heredoc> jk
pipe heredoc> k
pipe heredoc> kkk
pipe heredoc>
pipe heredoc> k
pipe heredoc> k
pipe heredoc> k
pipe heredoc> k
pipe heredoc> lim
pipe heredoc> littt
pipe heredoc> limitador
pipe heredoc> dsfsef
pipe heredoc> asgasrg
pipe heredoc> sgzardg
pipe heredoc> <egergt
pipe heredoc>
pipe heredoc>
➜  Pipex git:(master) ✗ grep hola << limit | cat >> outfile
pipe heredoc> kjbbubn
pipe heredoc> fhrh
pipe heredoc> tyjdtyj
pipe heredoc> tyjyhtdyh
pipe heredoc> hola
pipe heredoc> dgrds
pipe heredoc> thgrsth
pipe heredoc> limit
➜  Pipex git:(master) ✗ ./pipex_bonus here_doc limit ls cat outfile.txt

# Debugging

while(paths[i])
{
       write(2,paths[i],ft_strlen(paths[i]));
       write(2,"\n",1);
       i++;
}

write(2,"cmd_path\n",9);
write(2,cmd_path,ft_strlen(cmd_path));
write(2,"\n",1);

# Bonus

### Ejemplo de 3 Comandos

**En la Shell:**
```bash
< infile.txt | grep "hola" | sort | uniq > outfile3.txt
```
**En Pipex:**
```bash
./pipex_bonus infile.txt "grep 'hola'" "sort" "uniq" outfile3.txt
```

### Ejemplo de 4 Comandos

**En la Shell:**
```bash
cat infile.txt | grep "hola" | sort | uniq | wc -l > outfile4.txt
```
**En Pipex:**
```bash
./pipex_bonus infile.txt "grep 'hola'" "sort" "uniq" "wc -l" outfile4.txt
```

### Ejemplo de 5 Comandos

**En la Shell:**
```bash
cat infile.txt | grep "hola" | grep -v "que" | sort | uniq | wc -l > outfile5.txt
```
**En Pipex:**
```bash
./pipex infile.txt "grep 'hola'" "grep -v 'que'" "sort" "uniq" "wc -l" outfile5.txt
```

### Instrucciones para la Comparación:

1. **Preparación:** Asegúrate de que `infile.txt` exista y tenga contenido adecuado para las operaciones que vas a realizar.
   
2. **Ejecución en la Shell:** Ejecuta los comandos directamente en tu terminal o shell para generar los archivos de salida (`outfile3.txt`, `outfile4.txt`, `outfile5.txt`).

3. **Ejecución en Pipex:** Ejecuta los comandos equivalentes en tu implementación de Pipex para generar los archivos de salida.

4. **Comparación de Resultados:** Compara el contenido de los archivos de salida generados por la shell y por Pipex. Los resultados deben ser idénticos, indicando que tu programa maneja correctamente las tuberías (pipes) y redirecciones de archivos.

Esta estructura asegura que cada ejemplo comienza leyendo de `infile.txt` y termina escribiendo a un `outfile.txt` específico, lo cual es coherente con el comportamiento esperado para Pipex.

# TEST Part 1:

./pipex "tests/file1" "ls -l" "awk '{count++} END {printf count}'" output

<tests/file1 ls -l | awk '{count++} END {printf count}' >outfile

./pipex tests/file3 "tr '[:lower:]' '[:upper:]'" "grep PIPEX" output

<tests/file3 tr '[:lower:]' '[:upper:]' | grep PIPEX >outfile

./pipex tests/file2 "uniq" "wc -l" output

<tests/file2 uniq | wc -l >outfile

./pipex tests/file2 "sort" "uniq" output

<tests/file2 sort | uniq >outfile

./pipex tests/file2 "grep -i artificial" "wc -l" output

<tests/file2 grep -i artificial | wc -l >outfile

## Error arguments:

./pipex tests/file2 "sort" output

./pipex tests/file2 "sort" "uniq" "wc" output

./pipex tests/file2 "" "uniq" output -> Deberia de dar error

<tests/file2 "" | uniq >outfile

## Error cmds:

./pipex tests/file2 "sor" "uni" output

<tests/file2 sor | uni >outfile

## Error infile:

./pipex tests/file0 "uniq" "wc -l" output

<tests/file0 uniq | wc -l >outfile

## Error outfile:

chmod 000 output

chmod 000 outfile

./pipex tests/file2 "sort" "uniq" output

<tests/file2 sort | uniq >outfile

chmod 644 output

chmod 644 outfile

# TEST Bonus:

## multiples comandos

./pipex_bonus tests/file2 "sort" "uniq" "wc" output

<tests/file2 sort | uniq | wc >outfile

./pipex_bonus tests/file2 "sort" "wc" output

<tests/file2 sort | wc >outfile

./pipex_bonus tests/file2 "uniq" "wc" output

<tests/file2 uniq | wc >outfile

./pipex_bonus tests/file2 "uniq" "sort -r" output

<tests/file2 uniq | sort -r >outfile

./pipex_bonus tests/file2 "1" "2" "3" output

<tests/file2 1 | 2 | 3 >outfile

./pipex_bonus tests/file2 "uniq" output -> solo un comando debe dar error

./pipex_bonus tests/file2 output -> solo un comando debe dar error

./pipex_bonus tests/file2 "" "sort" output -> Deberia de procesar error xq un comando no es valido

<tests/file2 "" | sort >outfile

./pipex_bonus tests/file2 "uniq" "" output

<tests/file2 uniq | "" >outfile

./pipex_bonus tests/file2 "sort" "uniq" "" output

<tests/file2 sort | uniq | "" >outfile

./pipex_bonus tests/file2 "uniq" " " "sort" output -> debía dar error

<tests/file2 uniq | " " | sort >outfile

## here_doc

./pipex_bonus here_doc END sort output 

sort << END >> outfile

./pipex_bonus here_doc END sort uniq output -> solo un comando debe dar error

sort << END | uniq >> outfile

./pipex_bonus here_doc END "grep 'a'" "uniq" "ls" output

grep 'a' << END | uniq | ls >> outfile

./pipex_bonus here_doc limit "" "ls" output 

./pipex_bonus here_doc limit "ls" "" output

# NO LOS PASA:

## BONUS

./pipex_bonus here_doc END sor uni output -> me intenta buscar la ruta del outfile, salen 3 errores de ruta

sor << END | uni >> outfile

./pipex_bonus here_doc END sort uniq wc output
       1       3      25
sort << END | uniq | wc >> outfile
       3       3      15