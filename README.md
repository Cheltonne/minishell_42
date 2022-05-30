# minishell_42
The minishell project consists of coding a somewhat minimalist shell, taking bash as an exemple for implementing the following features and behaviors :
Syntax lexing/parsing.
Execution of simple commands using execve.
Recoding these builtin commands with no options : cd, pwd, env, export, unset, echo (with -n option).
Pipes (any number of them).
Redirections : <, <<, >, >>.
Variable expansion using the $ sign.
Accurate command exit codes as verified using the $? environment variable.
Signals (discriminating between interactive and non-interactive modes): Ctrl + C, Ctrl + D, Ctrl + \

To try :
Simply clone, make and launch ./minishell. If necessary, install the readline C library via <code>sudo apt-get install libreadline6 libreadline6-dev</code>
