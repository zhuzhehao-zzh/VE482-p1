#include "execute.h"

extern pid_t pid_form[BACKGROUND][PIPESIZE];

int check_o_redirect(char args[][ARGUMENTLEN]){
    int index = 0;
    int first_red = ARGUMENTSIZE;
    int last_pipe = 0;
    while(args[index][0]!='\0'){
        if(args[index][0]=='>'){
            if(index < first_red){
                first_red = index;
            }
        }
        if(args[index][0]=='|' && args[index][ARGUMENTLEN-1]!='a') last_pipe = index;
        index++;
    }
    if(last_pipe!=0 ){
        if(first_red<last_pipe) return 1;
    }
    return 0;
}

void execute_pipe(char args[][ARGUMENTLEN], int index, int p[2], int bg, int num)
{
    if(check_o_redirect(args)){
        printf("error: duplicated output redirection\n");
        return;
    }
    int next = index;
    while (next < ARGUMENTSIZE && (args[next][0] != '|' || args[next][ARGUMENTLEN - 1] == 'a') && args[next][0] != '\0')
        next++;
    if (next == ARGUMENTSIZE)
        return;
    if(next == index){
        printf("error: missing program\n");
        return;
    }
    int new_p[2];
    pipe(new_p);
    pid_t pid = fork();
    if (pid == 0)
    {
        if (index == 0)
        {
            close(new_p[0]);
            if (args[next][0] == '|')
            {
                dup2(new_p[1], 1);
            }
            else
                close(new_p[1]);
        }
        else if (args[next][0] == '|')
        {
            dup2(p[0], 0);
            close(new_p[0]);
            dup2(new_p[1], 1);
        }
        else
        {
            close(new_p[0]);
            close(new_p[1]);
            dup2(p[0], 0);
        }

        if (execute(args, index))
            exit(1);
        exit(0);
    }
    else
    {
        signal(SIGINT, sig_no);
        close(new_p[1]);
        int r=0;
        if (args[next][0] == '\0')
        {
            close(new_p[0]);
            close(new_p[1]);
            if(bg==1){
                for(int i=0; i<PIPESIZE;++i){
                    if(pid_form[num][i]==0){
                        pid_form[num][i] = pid;
                        break;
                    }
                }
            }
            if(bg==0) waitpid(pid, &r, 0);
            return;
        }
        if(bg==1){
            for(int i=0; i<PIPESIZE;++i){
                if(pid_form[num][i]==0){
                    pid_form[num][i] = pid;
                    break;
                }
            }
        }
        execute_pipe(args, next + 1, new_p,bg,num);
        if(bg==0) waitpid(pid, &r, 0);
        
        return;
    }
}

int execute(char args[][ARGUMENTLEN], int starting_point)
{
    if (starting_point >= ARGUMENTSIZE)
        return -1;
    int pos = starting_point;
    if ((args[starting_point][0] == '>') || (args[starting_point][0] == '<'))
    {
        if ((args[starting_point][0] == '>') || (args[starting_point][0] == '<'))
        {
            pos = starting_point + 4;
        }
        else
        {
            pos = starting_point + 2;
        }
    }
    if (is_same(args[pos], "exit"))
    {
        return 1;
    }
    signal(SIGINT, sig_exe);
    int a = dup(STDIN_FILENO);
    int b = dup(STDOUT_FILENO);
    int input_redirection = 0;
    int output_redirection = 0;
    int fd1;
    int fd2;
    char *args_cp[ARGUMENTSIZE];
    for (int i = 0; i < ARGUMENTSIZE; ++i)
        args_cp[i] = NULL;
    int j = 0;
    for (int i = starting_point; i < ARGUMENTSIZE; ++i)
    {
        if (args[i][0] == '\0' || (args[i][0] == '|' && args[i][ARGUMENTLEN - 1] != 'a'))
            break;
        if (is_same(args[i], ">"))
        {
            if(output_redirection!=0){
                dup2(b,STDOUT_FILENO);
                printf("error: duplicated output redirection\n");
                exit(0);
            }
            fd1 = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
            if(fd1==-1){
                printf("%s: Permission denied\n",args[i+1]);
                exit(0);
            }
            output_redirection = 1;
            dup2(fd1, STDOUT_FILENO);
            ++i;
            continue;
        }
        if (is_same(args[i], ">>"))
        {
            if(output_redirection!=0){
                dup2(b,STDOUT_FILENO);
                printf("error: duplicated output redirection\n");
                exit(0);
            }
            fd1 = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
            if(fd1==-1){
                printf("%s: Permission denied\n",args[i+1]);
                exit(0);
            }
            output_redirection = 1;
            dup2(fd1, STDOUT_FILENO);
            ++i;
            continue;
        }
        if (is_same(args[i], "<"))
        {
            if(starting_point!=0 || input_redirection!=0){
                printf("error: duplicated input redirection\n");
                exit(0);
            }
            fd2 = open(args[i + 1], O_RDONLY, 0777);
            if(fd2==-1){
                printf("%s: %s\n",args[i+1], strerror(errno));
                exit(0);
            }
            input_redirection = 1;
            dup2(fd2, STDIN_FILENO);
            ++i;
            continue;
        }
        args_cp[j] = args[i];
        ++j;
    }
    if(args_cp[0]==NULL){
        dup2(b,STDOUT_FILENO);
        printf("error: missing program\n");
        exit(0);
    }
    execvp(args_cp[0], args_cp);
    printf("%s: command not found\n", args_cp[0]);
    close(fd1);
    close(fd2);
    dup2(a, STDIN_FILENO);
    dup2(b, STDOUT_FILENO);
    close(a);
    close(b);
    exit(1);
    return 0;
}
