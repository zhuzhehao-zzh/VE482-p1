#include "accept.h"
#include "implement.h"
#include "execute.h"
#include "macro.h"

//use global variable, or use malloc, or use static?


pid_t pid_form[BACKGROUND][PIPESIZE];


int main(){
    //signal(SIGINT, sig_m);
    for(int i=0; i<BACKGROUND;++i){
        for(int j=0; j<PIPESIZE;++j){
            pid_form[i][j] = 0;
        }
    }
    char bg_form[BACKGROUND][BUFFSIZE];
    int num = 0;
    while(1){
        int bg=0;
        printf("mumsh $ ");
        fflush(stdout);
        signal(SIGINT, sig_m);
        char sin[BUFFSIZE];
        for(int i=0; i<BUFFSIZE;++i) sin[i] = '\0';
        int rv = accept(sin);
        if(rv==1){
            printf("exit\n");
            exit(0);
        }
        if(rv==2){
            continue;
        }
        if( strlen(sin) == 0){
            continue;
        }
        if(whe_bg(sin)==1){
            strcpy(bg_form[num],sin);
            ++num;
            printf("[%d] %s\n",num,sin);
            bg = 1;
        }
        char args[ARGUMENTSIZE][ARGUMENTLEN];
        for(int i=0; i<ARGUMENTSIZE;++i){
            for(int j=0; j<ARGUMENTLEN; ++j){
                args[i][j] = '\0';
            }
        }
        implement(sin,args);
        fflush(stdout);
        if(is_same(args[0],"exit")){
            printf("exit\n");
            break;
        }

        if(is_same(args[0],"cd")){
            int err = chdir(args[1]);
            if(err==-1)printf("%s: No such file or directory\n",args[1]);
            continue;
        }
        int p[2] = {0,0}; 
        if(bg==1){
            int i=0;
            while(i<ARGUMENTSIZE){
                if(args[i][0]=='\0') break;
                if(args[i][0]=='&'){
                    args[i][0] = '\0';
                    break;
                }
                ++i;
            }
        }

        if(is_same(args[0],"jobs")){
            for(int i=0; i<num; ++i){
                printf("[%d] ",i+1);
                char* stat = "done";
                for(int j=0; j<PIPESIZE; ++j){
                    if(pid_form[i][j]==0) break;
                    //printf("%d\n",j);
                    if(waitpid(pid_form[i][j], NULL, WNOHANG)==0){
                        stat = "running";
                        break;
                    }
                }
                printf("%s %s\n", stat, bg_form[i]);
                fflush(stdout);
            }
            continue;
        }
        execute_pipe(args,0,p,bg,num-1);
        // if(execute_pipe(args,0,p)){
        //     printf("exit\n");
        //     break;
        // }
    }
    return 0;
}
