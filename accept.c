#include "accept.h"
#include "implement.h"

int check(char sin[]){
    int double_quo = 0;
    int single_quo = 0;
    int index = 0;
    while(index<BUFFSIZE && sin[index]!='\0'){
        if(sin[index]=='\''){
            if(single_quo==0) single_quo=1;
            else single_quo = 0;
        }
        if(sin[index]=='\"'){
            if(double_quo==0) double_quo = 1;
            else double_quo = 0;
        }
        index++;
    }
    if(double_quo!=0 || single_quo!=0) return 0;
    if(sin[index-2]=='>' || sin[index-2]=='|' || sin[index-2]=='<' ) return 1;
    return 2;
}


int accept(char sin[]){
    fgets(sin, BUFFSIZE, stdin);
    if(feof(stdin)) return 1;
    if(strlen(sin)==1){
        sin[0] = '\0';
        return 0; 
    }
    while(check(sin)!=2){
        size_t kk = strlen(sin)-1;
        char k = sin[kk];
        sin[kk] = '\0';
        char er = check_syntax_error(sin);
        if(er!='\0'){
            printf("syntax error near unexpected token `%c'\n",er);
            return 2;
        }
        sin[kk] = k;
        printf("> ");
        if(check(sin)==1) sin[strlen(sin)-1] = ' ';
        fgets(sin+strlen(sin),BUFFSIZE,stdin);
        //sin[strlen(sin)-1] = '\0';
    }
    sin[strlen(sin)-1] = '\0';
    char er = check_syntax_error(sin);
    if(er!='\0'){
        printf("syntax error near unexpected token `%c'\n",er);
        return 2;
    }
    // printf("%s\n", sin);
    // fflush(stdout);
    return 0;
}
