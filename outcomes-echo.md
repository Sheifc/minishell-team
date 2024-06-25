# minishell

➜  minishell git:(main) ✗ ./minishell echo     

➜  minishell git:(main) ✗ ./minishell echo hola              
hola
➜  minishell git:(main) ✗ ./minishell echo -n
➜  minishell git:(main) ✗ ./minishell echo -n hola
hola%                                                                            
➜  minishell git:(main) ✗ ./minishell echo hola -n
hola -n
➜  minishell git:(main) ✗ ./minishell echo -n -n hola
hola%                                                                            
➜  minishell git:(main) ✗ ./minishell echo -n -n -n hola
hola%                                                                            
➜  minishell git:(main) ✗ ./minishell echo -nn hola     
hola%                                                                            
➜  minishell git:(main) ✗ ./minishell echo -nhola  
-nhola
➜  minishell git:(main) ✗ ./minishell echo -nnnnn hola
hola%                                                                           
➜  minishell git:(main) ✗ ./minishell echo -nn-nnn hola
-nn-nnn hola
➜  minishell git:(main) ✗ ./minishell echo hola -nnnholannnnn
hola -nnnholannnnn
➜  minishell git:(main) ✗

# bash

bash-3.2$ echo

bash-3.2$ echo hola
hola
bash-3.2$ echo -n
bash-3.2$ echo -n hola
holabash-3.2$ echo hola
hola
bash-3.2$ echo hola -n
hola -n
bash-3.2$ echo -n -n hola
holabash-3.2$ echo -n -n -n hola
holabash-3.2$ echo -nn hola
holabash-3.2$ echo -nhola
-nhola
bash-3.2$ echo -nnnnn hola
holabash-3.2$ echo -nn-nnn hola
-nn-nnn hola
bash-3.2$ echo hola -nnnholannnnn
hola -nnnholannnnn
bash-3.2$ exit
exit