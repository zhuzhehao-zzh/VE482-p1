# Zhehao Zhu's 4821 Project 1

# Commit

This project is restored in gitea of my department before, so information of commits cannot be uploaded.

# Build Badge

The whole project is consists of 10 files, which are `accept.c`, `accept.h`, `execute.c`, `execute.h`, `implement.c`, `implement.h`, `macro.c`, `macro.h`, `main.c`, and `Makefile`.
* `main.c`: Main function, realize while loop and connect different parts of obejcts.
* `accept.c`, `accept.h`: Accept the input and wait for completed commands.
* `implement.c`, `implement.h`: Implement the whole input into small units, including pipe, background commands, and so on.
* `execute.c`, `execute.h`: Execute the command, supporting pipes and background commands.
* `macro.c`, `macro.h`: Define macros and some helping functions.
* `Makefile`: Implement some building commands.

The structure and logic of this shell are as follows.
1. Main function implements the while loop and detect some commands such as `exit` and `CTRL+D`.
2. Main function calls `accept()` to get input from users.
3. Main function calls `implement()` to split a command into small units so that it's convenient for `execvp()` to work.
4. Main function calls `execute()` to execute commands

## Build and Installation

```bash
git remote add origin ssh://git@focs.ji.sjtu.edu.cn:2222/ECE482-22/ZhehaoZhu519030910143-p1.git
git pull origin master
make all
```

## Running instructions

In the terminal, run `./mumsh`, then you can use it as a shell. Here are some supporting commands:
* Single commands without arguments. `ls`
* Commands with arguments. `ls -l`
* File I/O redirection
* Pipe
* `CTRL C` and `CTRL D`
* Built-in command. `cd`
* Quotes and imcomplete quotes.
* Wait for commands to be completed
* Background process and `jobs`.

## Author information

Email: 519030910143@sjtu.edu.cn
