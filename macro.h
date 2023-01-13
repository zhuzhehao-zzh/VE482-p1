#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFSIZE 1024
#define ARGUMENTSIZE 100
#define ARGUMENTLEN 50
#define BACKGROUND 100
#define PIPESIZE 100

extern pid_t pid_form[BACKGROUND][PIPESIZE];


int is_special_1(char args[][ARGUMENTLEN], int index);
int is_special_2(char args[][ARGUMENTLEN], int index);
char check_syntax_error(char* sin);
int is_same(char a[], char* b);
void sig_m(int a);
void sig_exe(int a);
void sig_no(int a);
int whe_bg(char* sin);


#endif
