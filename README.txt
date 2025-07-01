valgrind --leak-check=full --show-leak-kinds=all --suppressions=supress.supp ./minishell 

!!! pred eval minishell_utils odkomentovat riadok ktory iOS nechcel skompilovat (preto nefunguje CONTROL + C)

DEBUG:
7. echo single quotes something to do with heredoc fix later
9. handle properly all exit statuses
10. if "unset HOME" and then "echo $HOME" not working



FIXED:
1. in cat ctrl + C - printuje 2x
2. env PATH - shuld not work (invlaid number of arguments)
3. ctrl-\ in cat without arguments - ma core dumpnut
6. export without arguments should print all exported variables
5. if NEW_VAR exist replace the value of NEW_VAR not working (creating new var)
8. unset" max number of params is ONE MAX
4. echo ' (variable value) 


