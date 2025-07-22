valgrind --leak-check=full --show-leak-kinds=all --suppressions=supress.supp ./minishell

echo "'$USER'"
should expand

----------------

huahmad@c2r9s5:~/a$ "$a" dsygf sduyg | ls
fucks up all execution



minishell$ cat << db
> ^C
echo $? 
0   


**************************** FIXED *****************************
huahmad@Sam:~/final$ ./minishell
minishell$ echo >>>>>>>>
minishell: syntax error near unexpected token
minishell: syntax error near unexpected token
minishell$ echo $?
minishell$

minishell$
exit
==29007==
==29007== HEAP SUMMARY:
==29007==     in use at exit: 208,448 bytes in 241 blocks
==29007==   total heap usage: 773 allocs, 532 frees, 262,049 bytes allocated
==29007==
==29007== 2 bytes in 1 blocks are definitely lost in loss record 1 of 67
==29007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==29007==    by 0x10F6BA: do_conversion (in /home/huahmad/21.7/minishell)
==29007==    by 0x10F659: ft_itoa (in /home/huahmad/21.7/minishell)
==29007==    by 0x10AD7F: handle_variable_expansion (create_command_list_utils.c:43)
==29007==    by 0x10DFDC: expand_variables (expansion.c:32)
==29007==    by 0x10ACAF: find_variables (create_command_list_utils.c:23)
==29007==    by 0x10A99D: var_and_quote_handling (create_command_list.c:46)
==29007==    by 0x10A91B: create_command_list (create_command_list.c:37)
==29007==    by 0x109E44: minishell_loop (minishell.c:48)
==29007==    by 0x109D68: main (minishell.c:29)

^Cminishell$ cat < db
cat: -: Bad file descriptor
hasam did some magic with his quick fix

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









huahmad@c2r9s5:~/a$ echo | |
bash: syntax error near unexpected token `|'
huahmad@c2r9s5:~/a$ echo $?
2

minishell$ echo | |
minishell$ echo $?
1









minishell$ echo adshfsfdh > a > > >
open or dup2 error: Bad address
adshfsfdh
parsing error









minishell$ ls -n | ca
minishell$: ca: command not found
minishell$ echo $?
0

huahmad@c2r9s5:~/a$ ls -n | ca
ca: command not found
huahmad@c2r9s5:~/a$ echo $?
127

probable needs to be code from last command in pipe








(IF ALL BELLOW IS ONE CASE THEN FIXED!!!)
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

