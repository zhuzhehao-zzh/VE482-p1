#include "implement.h"

int dealing_quote(char* sin, char args[][ARGUMENTLEN], int index_s, int index_a){
    if(sin[index_s] != '\"' && sin[index_s] != '\'') return -1;
    int index_c = 0;
    while(index_c < ARGUMENTLEN && args[index_a][index_c] != '\0') index_c++;
    int index_cp = index_s+1;
    while(sin[index_cp]!='\0' && sin[index_cp]!=sin[index_s]){
        args[index_a][index_c] = sin[index_cp];
        if(args[index_a][index_c]=='|' || args[index_a][index_c]=='<' || args[index_a][index_c]=='>' ) args[index_a][ARGUMENTLEN-1] = 'a';
        index_c++;
        index_cp++;
    }
    return index_cp;

}


void implement(char* sin, char args[][ARGUMENTLEN]){
    int j=0;
    // printf("SDA\n");
    // fflush(stdout);
    for(int i=0; i<BUFFSIZE;++i){
        // printf("%d\n",i);
        // fflush(stdout);
        if(sin[i]=='\0') break;
        if(sin[i]==' ') continue;
        //if(sin[i]=='\n') continue;
        if(sin[i]=='\'' || sin[i]=='\"'){
            if(i!=0 && sin[i-1]!=' ' && sin[i-1]!='>' && sin[i-1]!='<' ) --j;
            i = dealing_quote(sin,args,i,j);
            ++j;
            continue;
        }
        if(sin[i]=='|'){
            args[j][0] = '|';
            ++j;
            continue;
        }
        if(sin[i]=='<'){
            args[j][0] = '<';
            ++j;
            continue;
        }
        if(sin[i]=='>'){
            if(sin[i+1]=='>'){
                args[j][0] = '>';
                args[j][1] = '>';
                ++j;
                ++i;
                continue;
            }
            else
            {
                args[j][0] = '>';
                ++j;
                continue;
            }
        }
        int k = i;
        while(sin[k]!=' ' && sin[k]!='>' && sin[k]!='<' && sin[k]!='\0' && sin[k]!='\n' && sin[k]!='|' && sin[k]!='\"' && sin[k]!='\''){
            args[j][k-i] = sin[k];
            ++k;
        }
        i = k-1;
        ++j;
    }
    return;
}
