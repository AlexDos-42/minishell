<img src="https://capsule-render.vercel.app/api?type=transparent&color=timeGradient&height=200&text=Minishell&fontSize=64&fontAlignY=40&fontColor=d6ace6" alt="header" width="100%" />

<p align="right">
<img src="https://badge42.herokuapp.com/api/project/alesanto/minishell" alt="AlexDos-42" />
</p>

The objective of this project is to create a simple shell.

## Compilation && Execution

To run the project
```
make && ./minishell
```
## Implementation

* Show a prompt when waiting for a new command

* Search and launch the right executable based on the PATH variable or by using
relative or absolute path

* It must implement the builtins like in bash:
* * echo with option ’-n’
* * cd with only a relative or absolute path
* * pwd without any options
* * export without any options
* * unset without any options
* * env without any options and any arguments
* * exit without any options

* ; in the command should separate commands like in bash

* ’ and " work like in bash except for multiline commands

* Redirections < > “>>” work like in bash except for file descriptor aggregation

* Pipes | work like in bash

* Environment variables ($ followed by characters) work like in bash

* $? work like in bash

* ctrl-C, ctrl-D and ctrl-\ have the same result as in bash
