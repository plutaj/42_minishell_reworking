echo "'$USER'"
should expand

minishell$ ls -n | ca
minishell$: ca: command not found
minishell$ echo $?
0

huahmad@c2r9s5:~/a$ ls -n | ca
ca: command not found
huahmad@c2r9s5:~/a$ echo $?
127

probable needs to be code from last command in pipe

----------------

minishell$ echo $?
130
minishell$ ^C
minishell$ echo $?
130
minishell$ ls | ca | ls
builtins     env_var.o        free_functions.c  minishell    minishell_utils.c
data_init.c  env_var_utils.c  free_functions.o  minishell.c  minishell_utils.o
data_init.o  env_var_utils.o  libft             minishell.h  parsing
env_var.c    execution        Makefile          minishell.o  pipes
minishell$ echo $?
0
minishell$ ls | ca 
minishell$: ca: command not found
minishell$ ^C
minishell$ ls | ca | ls
builtins     env_var.o        free_functions.c  minishell    minishell_utils.c
data_init.c  env_var_utils.c  free_functions.o  minishell.c  minishell_utils.o
data_init.o  env_var_utils.o  libft             minishell.h  parsing
env_var.c    execution        Makefile          minishell.o  pipes
minishell$ echo $?
130
minishell$ ls | ca | wc -l
hasam knows

huahmad@c2r9s5:~/a$ "$a" dsygf sduyg | ls
fucks up all execution

minishell$ $a
execve: Permission denied
minishell$ echo $?
126

huahmad@c2r9s5:~/a$ $a
huahmad@c2r9s5:~/a$ echo $?
0

minishell$ echo > > > > >
open or dup2 error: Bad address

minishell$ echo $?
0

huahmad@c2r9s5:~/a$ echo > > > > >
bash: syntax error near unexpected token `>'
huahmad@c2r9s5:~/a$ echo $?
2

minishell$ echo adshfsfdh > a > > >
open or dup2 error: Bad address
adshfsfdh
parsing error

^Cminishell$ cat < db
cat: -: Bad file descriptor
hasam did some magic with his quick fix

minishell$ cat << db
> adfsdf
> ^C
> ^C
> ^C
> ^C
> ^C
> ^C
> ^C
> ^C
> ^C
> ^C

should exit without execution on ctrl-c

huahmad@c2r9s5:~/a$ echo | |
bash: syntax error near unexpected token `|'
huahmad@c2r9s5:~/a$ echo $?
2

minishell$ echo | |
minishell$ echo $?
1



