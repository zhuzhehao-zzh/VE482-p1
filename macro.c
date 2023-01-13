#include "macro.h"
#include "implement.h"

int is_special_1(char args[][ARGUMENTLEN], int index){
    if(args[index][0]=='<' && args[index][ARGUMENTLEN-1]!='a'){
        return 1;
    }
    if(args[index][0]=='>' && args[index][ARGUMENTLEN-1]!='a'){
        return 1;
    }
    if(args[index][0]=='|' && args[index][ARGUMENTLEN-1]!='a'){
        return 1;
    }
    return 0;
}

int is_special_2(char args[][ARGUMENTLEN], int index){
    if(args[index][0]=='<' && args[index][ARGUMENTLEN-1]!='a'){
        return 1;
    }
    if(args[index][0]=='>' && args[index][ARGUMENTLEN-1]!='a'){
        return 1;
    }
    return 0;
}

char check_syntax_error(char* sin){
    char args[ARGUMENTSIZE][ARGUMENTLEN];
    for(int i=0; i<ARGUMENTSIZE;++i){
        for(int j=0; j<ARGUMENTLEN; ++j){
            args[i][j] = '\0';
        }
    }
    implement(sin,args);
    int index = 0;
    while(args[index][0]!='\0'){
        if(is_special_1(args,index) && index!=0 && is_special_2(args,index-1) ) return args[index][0];
        index++;
    }
    return '\0';
}

int is_same(char a[], char* b){
    size_t i=0;
    for(; i<strlen(b); ++i){
        if(a[i]!=b[i]) return 0;
    }
    if(a[i]!='\0') return 0;
    return 1;
}

void sig_m(int a){
    if(a==SIGINT){
        printf("\nmumsh $ ");
        fflush(stdout);
        return;
    }
    return;
}

void sig_exe(int a){
    if(a==SIGINT){
        printf("I'm exiting\n");
        fflush(stdout);
        exit(0);
    }
    exit(0);
    return;
}

void sig_no(int a){
    if(a==SIGINT) return;
    return;
}

int whe_bg(char* sin){
    if(strlen(sin)==0) return 0;
    if(sin[strlen(sin)-1]=='&') return 1;
    return 0;
}
